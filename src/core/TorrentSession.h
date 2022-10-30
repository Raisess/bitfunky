#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <libtorrent/session.hpp>
#include "TorrentDownload.h"

namespace BF {

class TorrentSession {
public:
  static bool KeepRunning;

  TorrentSession();
  ~TorrentSession();

  void push_download(const std::shared_ptr<TorrentDownload>&);
  void push_download(const std::vector<std::shared_ptr<TorrentDownload>>&);
  void loop(const std::function<void(void)>&); // Secure loop, clean shared ptr's on interrupt signal
  void handle();

private:
  std::vector<std::shared_ptr<TorrentDownload>> queue;
  std::unique_ptr<lt::session> lt_session = nullptr;

  static void HandleInterruptSignal(int) {
    KeepRunning = false;
  }
};

}
