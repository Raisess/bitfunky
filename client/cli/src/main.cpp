#include <iostream>
#include <memory>
#include <vector>
#include <bitfunky/util/Logger.h>
#include <bitfunky/util/Time.h>
#include <bitfunky/TorrentDownload.h>
#include <bitfunky/TorrentSession.h>
#include <cli-creator/Cli.h>

#define DEFAULT_OUTPUT "."
#define ALIAS_MAX_PRINT_SIZE 30

using namespace CliCreator;

auto download_torrent = [](Arguments args) -> int {
  try {
    std::vector<std::shared_ptr<BF::TorrentDownload>> torrents = {};
    for (auto arg : args) {
      torrents.push_back(BF::TorrentDownload::CreateFromTorrent(arg, arg, DEFAULT_OUTPUT));
    }

    BF::TorrentSession session;
    session.push_download(torrents);

    while (true) {
      std::system("clear");

      std::cout << "-----> BitFunky Client" << std::endl;
      for (auto torrent : torrents) {
        const auto alias = torrent->get_alias();
        std::cout << (alias.size() <= ALIAS_MAX_PRINT_SIZE ? alias : alias.substr(0, ALIAS_MAX_PRINT_SIZE) + "...");
        std::cout << " ";
        BF::Util::Logger::PrintTorrentState(torrent->state);
      }
      std::cout << std::endl << "Thanks for using BitFunky CLI @ Raisess" << std::endl;

      session.handle();
      BF::Util::Time::Sleep(200);
    }

    return 0;
  } catch (std::exception& err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }
};

auto help = [](Arguments) -> int {
  std::cout << "-----> BitFunky CLI Commands" << std::endl;
  std::cout << "\t--torrent | -t: Download torrents" << std::endl;
  std::cout << "\t\tE.g.: --torrent=/path/file.torrent,/path/file.torrent" << std::endl;
  std::cout << "\t--help | -h: Show help" << std::endl;
  std::cout << std::endl << "Thanks for using BitFunky CLI @ Raisess" << std::endl;
  return 0;
};

int main(int argc, char* argv[]) {
  Cli cli;

  cli.commands["--torrent"] = download_torrent;
  cli.commands["-t"] = download_torrent;
  cli.commands["--help"] = help;
  cli.commands["-h"] = help;

  return cli.handle(argc, argv);
}
