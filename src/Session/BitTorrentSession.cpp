#include <chrono>
#include <iostream>
#include <thread>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/session_params.hpp>
#include "BitTorrentSession.h"

AG::BitTorrentSession::BitTorrentSession() : Session<BitTorrentDownload>() {
  lt::settings_pack lt_settings;
  lt_settings.set_int(
    lt::settings_pack::alert_mask,
    lt::alert_category::error
    | lt::alert_category::status
    | lt::alert_category::storage
  );
  this->lt_session = std::make_unique<lt::session>(lt_settings);
}

AG::BitTorrentSession::~BitTorrentSession() {}

void AG::BitTorrentSession::push_download(const std::shared_ptr<BitTorrentDownload>& torrent) {
  torrent->state.status = DownloadState::Status::ACTIVE;
  this->lt_session->add_torrent(torrent->get_lt_params());
  this->queue.push_back(torrent);
}

void AG::BitTorrentSession::push_download(const std::vector<std::shared_ptr<BitTorrentDownload>>& torrents) {
  for (auto torrent : torrents) {
    this->push_download(torrent);
  }
}

void AG::BitTorrentSession::handle(const std::function<void(void)>& callback) {
  try {
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

          switch (torrent->state.status) {
            case DownloadState::Status::ACTIVE:
              {
                auto status = state->status[i];
                if (status.is_finished) {
                  torrent->state.status = DownloadState::Status::FINISHED;
                }

                torrent->state.progress = status.progress_ppm / 10000;
                torrent->state.total_downloaded = status.total_done / 1000;
                torrent->state.download_rate = status.download_payload_rate / 1000;
                torrent->state.peers = status.num_peers;
              }
              break;
            case DownloadState::Status::FINISHED:
              {
                auto status = state->status[i];
                if (status.is_seeding) {
                  torrent->state.status = DownloadState::Status::SEEDING;
                }
              }
              break;
            // TODO: Sedding and paused state status update
            case DownloadState::Status::SEEDING:
            case DownloadState::Status::PAUSED:
              break;
            // Do nothing states
            case DownloadState::Status::CREATED:
            case DownloadState::Status::FAILED:
              break;
          }
        }
      }
    }

    callback();
    this->lt_session->post_torrent_updates();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    return;
  } catch (std::exception& err) {
    std::cerr << "Error: " << err.what() << std::endl;
    return;
  }
}
