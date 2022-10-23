#include <chrono>
#include <iostream>
#include <thread>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/session_params.hpp>
#include "Session.h"

AG::Session::Session() {
  lt::settings_pack lt_settings;
  lt_settings.set_int(
    lt::settings_pack::alert_mask,
    lt::alert_category::error
    | lt::alert_category::status
    | lt::alert_category::storage
  );
  this->lt_session = std::make_unique<lt::session>(lt_settings);
}

AG::Session::~Session() {}

void AG::Session::push(const std::shared_ptr<Torrent>& torrent) {
  torrent->status.state = TorrentStatus::State::ACTIVE;
  this->lt_session->add_torrent(torrent->get_lt_params());
  this->queue.push_back(torrent);
}

void AG::Session::push(const std::vector<std::shared_ptr<Torrent>>& torrents) {
  for (auto torrent : torrents) {
    this->push(torrent);
  }
}

int AG::Session::handle(const std::function<void(void)>& callback) {
  try {
    while (true) {
      std::vector<lt::alert*> lt_alerts;
      this->lt_session->pop_alerts(&lt_alerts);

      for (auto alert : lt_alerts) {
        if (lt::alert_cast<lt::torrent_error_alert>(alert)) {
          break;
        }

        auto state = lt::alert_cast<lt::state_update_alert>(alert);
        if (state) {
          if (state->status.empty()) continue;

          for (size_t i = 0; i < state->status.size(); i++) {
            auto torrent = this->queue[i];

            switch (torrent->status.state) {
              case TorrentStatus::State::ACTIVE:
                {
                  auto status = state->status[i];
                  if (status.is_finished) {
                    torrent->status.state = TorrentStatus::State::FINISHED;
                  }

                  torrent->status.progress = status.progress_ppm / 10000;
                  torrent->status.total_downloaded = status.total_done / 1000;
                  torrent->status.download_rate = status.download_payload_rate / 1000;
                  torrent->status.peers = status.num_peers;
                }
                break;
              case TorrentStatus::State::FINISHED:
                {
                  auto status = state->status[i];
                  if (status.is_seeding) {
                    torrent->status.state = TorrentStatus::State::SEEDING;
                  }
                }
                break;
              // TODO: Sedding and paused state status update
              case TorrentStatus::State::SEEDING:
              case TorrentStatus::State::PAUSED:
                break;
              // Do nothing states
              case TorrentStatus::State::CREATED:
              case TorrentStatus::State::FAILED:
                break;
            }
          }
        }
      }

      this->lt_session->post_torrent_updates();
      callback();
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "Finished!" << std::endl;
    return 0;
  } catch (std::exception& err) {
    std::cerr << "Error: " << err.what() << std::endl;
    return 1;
  }
}
