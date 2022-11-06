#pragma once

void print_header() {
  std::cout << "-----> BitFunky CLI" << std::endl << std::endl;
}

static std::string get_progress_bar(uint8_t progress) {
  std::string progress_bar = "--------------------";
  uint8_t chunk = progress / 5;

  for (int i = 0; i < chunk; i++) {
    progress_bar.replace(i, 1, "#");
  }

  return "[" + progress_bar + "]";
}

#define ALIAS_MAX_PRINT_SIZE 30

void print_torrent_info(const std::string& alias, const BF::TorrentState& state) {
  std::cout << (alias.size() <= ALIAS_MAX_PRINT_SIZE ? alias : alias.substr(0, ALIAS_MAX_PRINT_SIZE) + "...");
  std::cout << " ";
  std::cout << get_progress_bar(state.progress);
  std::cout << " " << unsigned(state.progress) << "%";
  std::cout << " | " << unsigned(state.total_downloaded) << " kB";
  std::cout << " | " << unsigned(state.download_rate) << " kB/s";
  std::cout << " | " << "Status: " << state.status;
  std::cout << " | " << "Peers: " << state.peers << std::endl;
}

void print_footer() {
  std::cout << std::endl << "Thanks for using BitFunky @ Raisess" << std::endl;
}
