#include <csignal>
#include <iostream>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/torrent_flags.hpp>
#include <libtorrent/torrent_info.hpp>
#include "../util/File.h"
#include "../util/Util.h"
#include "TorrentSession.h"

bool BF::TorrentSession::KeepRunning = true;

BF::TorrentSession::TorrentSession() {
  this->lt_session = std::make_unique<lt::session>();

  if (!this->lt_session) {
    std::cerr << "Error creating TorrentSession" << std::endl;
    exit(1);
  }

  signal(SIGINT, TorrentSession::HandleMainLoopInterrupt);
}

BF::TorrentSession::~TorrentSession() {}

void BF::TorrentSession::push_download(const std::shared_ptr<TorrentDownload>& torrent) {
  if (torrent->is_magnet()) {
    auto add_torrent_params = lt::parse_magnet_uri(torrent->get_input());
    add_torrent_params.save_path = torrent->get_output();
    auto handler = this->lt_session->add_torrent(std::move(add_torrent_params));
    torrent->set_torrent_handle(std::move(handler));
  } else {
    auto torrent_info = lt::torrent_info(torrent->get_input());
    auto handler = this->lt_session->add_torrent(std::move(torrent_info), torrent->get_output());
    torrent->set_torrent_handle(std::move(handler));
  }

  torrent->state.status = TorrentDownloadState::Status::ACTIVE;
  this->queue.push_back(torrent);
}

void BF::TorrentSession::push_download(const std::vector<std::shared_ptr<TorrentDownload>>& torrents) {
  for (auto torrent : torrents) {
    this->push_download(torrent);
  }
}

void BF::TorrentSession::loop(const std::function<void(void)>& callback) {
  while (TorrentSession::KeepRunning) {
    this->handle();
    callback();
    Util::Sleep(200);
  }
}

void BF::TorrentSession::loop() {
  while (TorrentSession::KeepRunning) {
    this->handle();
    Util::Sleep(200);
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

void BF::TorrentSession::save_info() {
  File f(SESSION_INFO_FILE);
  f.write("");

  for (auto torrent : this->queue) {
    f.append(torrent->serialize());
  }
}
