#pragma once

#include <cstdint>
#include <iostream>
#include "../TorrentDownload.h"

namespace BF {
namespace Util {

class Logger {
public:
  static void PrintTorrentState(const BF::TorrentDownloadState& state) {
    std::cout << Logger::GetProgressBar(state.progress);
    std::cout << " " << unsigned(state.progress) << "%";
    std::cout << " | " << unsigned(state.total_downloaded) << " kB";
    std::cout << " | " << unsigned(state.download_rate) << " kB/s";
    std::cout << " | " << "Status: " << state.status;
    std::cout << " | " << "Peers: " << state.peers << std::endl;
  }

private:
  static const std::string GetProgressBar(uint8_t progress) {
    std::string progress_bar = "--------------------";
    uint8_t chunk = progress / 5;

    for (int i = 0; i < chunk; i++) {
      progress_bar.replace(i, 1, "#");
    }

    return "[" + progress_bar + "]";
  }
};

}
}
