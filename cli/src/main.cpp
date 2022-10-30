#include <iostream>
#include <memory>
#include <vector>
#include <bitfunky/core/TorrentDownload.h>
#include <bitfunky/core/TorrentSession.h>
#include <bitfunky/util/Logger.h>
#include <cli-creator/Cli.h>

#define EXIT_KEY 'q'
#define DEFAULT_OUTPUT "."
#define ALIAS_MAX_PRINT_SIZE 30

using namespace CliCreator;

void print_header() {
  std::cout << "-----> BitFunky CLI" << std::endl << std::endl;
}

void print_fotter() {
  std::cout << std::endl << "Thanks for using BitFunky @ Raisess" << std::endl;
}

auto help = [](Arguments) {
  print_header();
  std::cout << "\t--torrent | -t: Download torrents" << std::endl;
  std::cout << "\t\tE.g.: --torrent=/path/file.torrent,/path/file.torrent" << std::endl;
  std::cout << "\t--help | -h: Show help" << std::endl;
  print_fotter();
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
        const auto alias = torrent->get_alias();
        std::cout << (alias.size() <= ALIAS_MAX_PRINT_SIZE ? alias : alias.substr(0, ALIAS_MAX_PRINT_SIZE) + "...");
        std::cout << " ";
        BF::Util::Logger::PrintTorrentState(torrent->state);
      }

      print_fotter();
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
