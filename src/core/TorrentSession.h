#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <libtorrent/session.hpp>
#include "Torrent.h"

#define SESSION_INFO_FILE "./session_info.txt"

namespace BF {

class TorrentSession {
public:
  TorrentSession();
  ~TorrentSession();

  void push_download(const std::shared_ptr<Torrent>&);
  void push_download(const std::vector<std::shared_ptr<Torrent>>&);
  void handle();
  void loop(const std::function<void(void)>&);
  void save_info();

private:
  std::vector<std::shared_ptr<Torrent>> queue;
  std::unique_ptr<lt::session> lt_session = nullptr;

  static bool KeepRunning;
  static void HandleMainLoopInterrupt(int) {
    TorrentSession::KeepRunning = false;
  }
};

}
