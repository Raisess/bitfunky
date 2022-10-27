#include <iostream>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/torrent_flags.hpp>
#include "TorrentSession.h"

BF::TorrentSession::TorrentSession() {
  this->lt_session = std::make_unique<lt::session>();

  if (!this->lt_session) {
    std::cerr << "Error creating TorrentSession" << std::endl;
    exit(1);
  }
}

BF::TorrentSession::~TorrentSession() {}

void BF::TorrentSession::push_download(const std::shared_ptr<TorrentDownload>& torrent) {
  auto add_torrent_params = lt::parse_magnet_uri(torrent->get_magnet_uri());
  add_torrent_params.save_path = torrent->get_output();
  torrent->set_torrent_handle(this->lt_session->add_torrent(add_torrent_params));
  torrent->state.status = TorrentDownloadState::Status::ACTIVE;
  this->queue.push_back(torrent);
}

void BF::TorrentSession::push_download(const std::vector<std::shared_ptr<TorrentDownload>>& torrents) {
  for (auto torrent : torrents) {
    this->push_download(torrent);
  }
}

void BF::TorrentSession::handle() {
  for (auto torrent : this->queue) {
    const auto handler = torrent->get_torrent_handle();
    const auto status = handler.status();

    torrent->state.progress = status.progress_ppm / 10000;
    torrent->state.total_downloaded = status.total_done / 1000;
    torrent->state.download_rate = status.download_payload_rate / 1000;
    torrent->state.peers = status.num_peers;

    switch (torrent->state.status) {
      case TorrentDownloadState::Status::ACTIVE:
        if (status.is_finished) {
          torrent->state.status = TorrentDownloadState::Status::FINISHED;
        }
        handler.unset_flags(lt::torrent_flags::paused);
        break;
      case TorrentDownloadState::Status::PAUSED:
        handler.set_flags(lt::torrent_flags::paused);
        break;
      case TorrentDownloadState::Status::FINISHED:
        if (status.is_seeding) {
          torrent->state.status = TorrentDownloadState::Status::SEEDING;
        }
        break;
      // TODO: Sedding state status update
      case TorrentDownloadState::Status::SEEDING:
        break;
      // Do nothing states
      case TorrentDownloadState::Status::CREATED:
      case TorrentDownloadState::Status::FAILED:
        break;
    }
  }
}