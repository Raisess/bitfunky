#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <libtorrent/session.hpp>
#include "TorrentDownload.h"

#define SESSION_INFO_FILE "./session_info.txt"

namespace BF {

class TorrentSession {
public:
  TorrentSession();
  ~TorrentSession();

  void push_download(const std::shared_ptr<TorrentDownload>&);
  void push_download(const std::vector<std::shared_ptr<TorrentDownload>>&);
  void handle();
  void loop(const std::function<void(void)>&);
  void save_info();

private:
  std::vector<std::shared_ptr<TorrentDownload>> queue;
  std::unique_ptr<lt::session> lt_session = nullptr;

  static bool KeepRunning;
  static void HandleMainLoopInterrupt(int) {
    TorrentSession::KeepRunning = false;
  }
};

}
