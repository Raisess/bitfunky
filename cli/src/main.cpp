#include <iostream>
#include <memory>
#include <vector>
#include <bitfunky/core/TorrentDownload.h>
#include <bitfunky/core/TorrentSession.h>
#include <bitfunky/util/Util.h>
#include <cli-creator/Cli.h>
#include "print.h"

#define DEFAULT_OUTPUT_PATH() BF::Util::Env("HOME") + "/Downloads"

using namespace CliCreator;

auto help = [](Arguments) {
  print_header();
  std::cout << "\t--torrent | -t: Download torrents" << std::endl;
  std::cout << "\t\tE.g.: --torrent=/path/file.torrent,/path/file.torrent" << std::endl;
  std::cout << "\t--help | -h: Show help" << std::endl;
  print_footer();
  return 0;
};

void download(const std::vector<std::shared_ptr<BF::TorrentDownload>>&);

auto download_torrent = [](Arguments args) {
  if (args.size() == 0) {
    std::cerr << "Invalid argument, no file provided." << std::endl;
    return 1;
  }

  std::vector<std::shared_ptr<BF::TorrentDownload>> torrents = {};
  for (auto arg : args) {
    torrents.push_back(BF::TorrentDownload::Create(arg, arg, DEFAULT_OUTPUT_PATH()));
  }

  try {
    download(torrents);
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

void download(const std::vector<std::shared_ptr<BF::TorrentDownload>>& downloads) {
  BF::TorrentSession session;
  session.push_download(downloads);

  session.loop([downloads]() {
    std::system("clear");
    print_header();

    for (auto download : downloads) {
      print_torrent_info(download->get_alias(), download->state);
    }

    print_footer();
  });
}
