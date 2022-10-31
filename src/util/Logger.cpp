#include <cstdint>
#include <iostream>
#include "Logger.h"

static std::string get_progress_bar(uint8_t);

void BF::Logger::PrintTorrentState(const BF::TorrentDownloadState& info) {
  std::cout << get_progress_bar(info.progress);
  std::cout << " " << unsigned(info.progress) << "%";
  std::cout << " | " << unsigned(info.total_downloaded) << " kB";
  std::cout << " | " << unsigned(info.download_rate) << " kB/s";
  std::cout << " | " << "Status: " << info.status;
  std::cout << " | " << "Peers: " << info.peers << std::endl;
}

static std::string get_progress_bar(uint8_t progress) {
  std::string progress_bar = "--------------------";
  uint8_t chunk = progress / 5;

  for (int i = 0; i < chunk; i++) {
    progress_bar.replace(i, 1, "#");
  }

  return "[" + progress_bar + "]";
}
