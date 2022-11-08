#include <csignal>
#include <iostream>
#include <libtorrent/load_torrent.hpp>
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/torrent_handle.hpp>
#include "../util/File.h"
#include "../util/Util.h"
#include "TorrentSession.h"

BF::TorrentSession::TorrentSession() {
  this->lt_session = std::make_unique<lt::session>();

  if (!this->lt_session) {
    std::cerr << "Error creating TorrentSession" << std::endl;
    exit(1);
  }
}

BF::TorrentSession::~TorrentSession() {}

void BF::TorrentSession::push_download(const std::shared_ptr<Torrent>& torrent) {
  auto add_torrent_params = torrent->is_magnet()
    ? lt::parse_magnet_uri(torrent->get_input())
    : lt::load_torrent_file(torrent->get_input());
  add_torrent_params.save_path = torrent->get_output();
  auto handler = this->lt_session->add_torrent(std::move(add_torrent_params));
  torrent->handler = std::make_unique<lt::torrent_handle>(std::move(handler));

  torrent->state.status = TorrentState::Status::ACTIVE;
  this->queue.push_back(torrent);
}

void BF::TorrentSession::push_download(const std::vector<std::shared_ptr<Torrent>>& torrents) {
  for (auto torrent : torrents) {
    this->push_download(torrent);
  }
}

void BF::TorrentSession::handle() {
  for (auto torrent : this->queue) {
    if (torrent == nullptr) continue;

    const auto status = torrent->handler->status();
    torrent->state.progress = status.progress_ppm / 10000;
    torrent->state.total_downloaded = status.total_done / 1000;
    torrent->state.download_rate = status.download_payload_rate / 1000;
    torrent->state.peers = status.num_peers;

    switch (torrent->state.status) {
      case TorrentState::Status::ACTIVE:
        if (status.is_finished) {
          torrent->state.status = TorrentState::Status::FINISHED;
        }
        torrent->handler->unset_flags(lt::torrent_flags::paused);
        break;
      case TorrentState::Status::PAUSED:
        torrent->handler->set_flags(lt::torrent_flags::paused);
        break;
      case TorrentState::Status::FINISHED:
        if (status.is_seeding) {
          torrent->state.status = TorrentState::Status::SEEDING;
        }
        break;
      // TODO: Sedding state status update
      case TorrentState::Status::SEEDING:
        break;
      // Do nothing states
      case TorrentState::Status::CREATED:
      case TorrentState::Status::FAILED:
        break;
    }
  }
}

bool BF::TorrentSession::KeepRunning = true;
void BF::TorrentSession::loop(const std::function<void(void)>& callback) {
  signal(SIGINT, TorrentSession::HandleMainLoopInterrupt);

  while (TorrentSession::KeepRunning) {
    this->handle();
    callback();
    Util::Sleep(200);
  }
}

void BF::TorrentSession::save_info() {
  File f(SESSION_INFO_FILE);
  f.write("");

  for (auto torrent : this->queue) {
    f.append(torrent->serialize());
  }
}
