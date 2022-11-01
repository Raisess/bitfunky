#include <iostream>
#include <memory>
#include <vector>
#include <bitfunky/core/TorrentDownload.h>
#include <bitfunky/core/TorrentSession.h>
#include <cli-creator/Cli.h>

#define EXIT_KEY 'q'
#define DEFAULT_OUTPUT "."
#define ALIAS_MAX_PRINT_SIZE 30

using namespace CliCreator;

void print_header();
void print_torrent_info(const std::string& alias, const BF::TorrentDownloadState&);
void print_footer();

auto help = [](Arguments) {
  print_header();
  std::cout << "\t--torrent | -t: Download torrents" << std::endl;
  std::cout << "\t\tE.g.: --torrent=/path/file.torrent,/path/file.torrent" << std::endl;
  std::cout << "\t--help | -h: Show help" << std::endl;
  print_footer();
  return 0;
};

auto download_torrent = [](Arguments args) {
  try {
    if (args.size() == 0) {
      std::cerr << "Invalid argument, no file provided." << std::endl;
      return 1;
    }

    std::vector<std::shared_ptr<BF::TorrentDownload>> torrents = {};
    for (auto arg : args) {
      torrents.push_back(BF::TorrentDownload::Create(arg, arg, DEFAULT_OUTPUT));
    }

    BF::TorrentSession session;
    session.push_download(torrents);

    session.loop([torrents]() {
      std::system("clear");
      print_header();

      for (auto torrent : torrents) {
        print_torrent_info(torrent->get_alias(), torrent->state);
      }

      print_footer();
    });

    return 0;
  } catch (std::exception& err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }
};

int main(int argc, char* argv[]) {
  Cli cli;

  cli.commands["--help"] = help;
  cli.commands["-h"] = help;
  cli.commands["--torrent"] = download_torrent;
  cli.commands["-t"] = download_torrent;

  return cli.handle(argc, argv);
}

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

void print_torrent_info(const std::string& alias, const BF::TorrentDownloadState& state) {
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
