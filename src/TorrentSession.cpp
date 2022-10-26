#include <iostream>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/session_params.hpp>
#include "TorrentSession.h"

BF::TorrentSession::TorrentSession() {
  lt::settings_pack lt_settings;
  lt_settings.set_int(
    lt::settings_pack::alert_mask,
    lt::alert_category::error
    | lt::alert_category::status
    | lt::alert_category::storage
  );
  this->lt_session = std::make_unique<lt::session>(lt_settings);

  if (!this->lt_session) {
    std::cerr << "Error creating TorrentSession" << std::endl;
    exit(1);
  }
}

BF::TorrentSession::~TorrentSession() {}

void BF::TorrentSession::push_download(const std::shared_ptr<TorrentDownload>& torrent) {
  torrent->state.status = TorrentDownloadState::Status::ACTIVE;
  this->lt_session->add_torrent(torrent->get_add_torrent_params());
  this->queue.push_back(torrent);
}

void BF::TorrentSession::push_download(const std::vector<std::shared_ptr<TorrentDownload>>& torrents) {
  for (auto torrent : torrents) {
    this->push_download(torrent);
  }
}

void BF::TorrentSession::handle() {
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
            case TorrentDownloadState::Status::ACTIVE:
              {
                auto status = state->status[i];
                if (status.is_finished) {
                  torrent->state.status = TorrentDownloadState::Status::FINISHED;
                }

                torrent->state.progress = status.progress_ppm / 10000;
                torrent->state.total_downloaded = status.total_done / 1000;
                torrent->state.download_rate = status.download_payload_rate / 1000;
                torrent->state.peers = status.num_peers;
              }
              break;
            case TorrentDownloadState::Status::FINISHED:
              {
                auto status = state->status[i];
                if (status.is_seeding) {
                  torrent->state.status = TorrentDownloadState::Status::SEEDING;
                }
              }
              break;
            // TODO: Sedding and paused state status update
            case TorrentDownloadState::Status::SEEDING:
            case TorrentDownloadState::Status::PAUSED:
              break;
            // Do nothing states
            case TorrentDownloadState::Status::CREATED:
            case TorrentDownloadState::Status::FAILED:
              break;
          }
        }
      }
    }

    this->lt_session->post_torrent_updates();
    return;
  } catch (std::exception& err) {
    std::cerr << "Error: " << err.what() << std::endl;
    return;
  }
}
