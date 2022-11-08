#include <iostream>
#include <memory>
#include <vector>
#include <bitfunky/core/MagnetDatabase.h>
#include <bitfunky/core/TorrentSession.h>
#include <bitfunky/core/Torrent.h>
#include <cli-creator/Cli.h>
#include "print.h"

#define DEFAULT_OUTPUT_PATH "."

using namespace CliCreator;

auto help = [](Arguments) {
  print_header();
  std::cout << "\t--torrent | -t: Download torrent from a `.torrent` file" << std::endl;
  std::cout << "\t\tE.g.: --torrent=/path/file.torrent,/path/file.torrent" << std::endl;
  std::cout << "\t--magnet | -m: Download torrent from a `magnet-uri` at your magnet database" << std::endl;
  std::cout << "\t\tE.g.: --magnet=some-alias" << std::endl;
  std::cout << "\t--init-magnet | -im: Init a magnet database at `$HOME/.magnet_database.db`" << std::endl;
  std::cout << "\t\tE.g.: --init-magnet" << std::endl;
  std::cout << "\t--search-magnet | -sm: Search for matchs into magnet database" << std::endl;
  std::cout << "\t\tE.g.: --search-magnet=some-alias" << std::endl;
  std::cout << "\t--merge-magnet | -mm: Merge another magnet database into you current magnet database" << std::endl;
  std::cout << "\t\tE.g.: --merge-magnet=./path/another_magnet_database.db" << std::endl;
  std::cout << "\t--help | -h: Show help" << std::endl;
  print_footer();
  return 0;
};

auto init_magnet_db = [](Arguments) {
  BF::MagnetDatabase::Init();
  std::cout << "Magnet database initiated at: " << DEFAULT_SQLITE_DATABASE() << std::endl;
  return 0;
};

auto merge_magnet_db = [](Arguments args) {
  if (args.size() == 0) {
    std::cerr << "Invalid argument, no file provided." << std::endl;
    return 1;
  }

  BF::MagnetDatabase::Merge(args[0]);
  std::cout << "Merge finished!" << std::endl;
  return 0;
};

auto search_magnet_db = [](Arguments args) {
  if (args.size() == 0) {
    std::cerr << "Invalid argument, no alias provided." << std::endl;
    return 1;
  }

  BF::MagnetDatabase magnet_db;
  auto results = magnet_db.search(args[0]);
  for (auto result : results) {
    std::cout << "---> " << result.alias << " (" + result.create_date + "): " << result.magnet_uri << std::endl;
    std::cout << "-------------------------" << std::endl;
  }

  return 0;
};

void handle_download(const std::vector<std::shared_ptr<BF::Torrent>>&);

auto download_torrent = [](Arguments args) {
  if (args.size() == 0) {
    std::cerr << "Invalid argument, no file provided." << std::endl;
    return 1;
  }

  std::vector<std::shared_ptr<BF::Torrent>> torrents = {};
  for (auto arg : args) {
    torrents.push_back(BF::Torrent::Create(arg, arg, DEFAULT_OUTPUT_PATH));
  }

  try {
    handle_download(torrents);
    return 0;
  } catch (std::exception& err) {
    std::cerr << err.what() << std::endl;
    return 1;
  }
};

auto download_magnet = [](Arguments args) {
  if (args.size() == 0) {
    std::cerr << "Invalid argument, no alias provided." << std::endl;
    return 1;
  }

  BF::MagnetDatabase magnet_db;
  std::vector<std::shared_ptr<BF::Torrent>> magnets = {};
  for (auto arg : args) {
    auto result = magnet_db.find(arg);
    magnets.push_back(BF::Torrent::Create(result.alias, result.magnet_uri, DEFAULT_OUTPUT_PATH));
  }

  try {
    handle_download(magnets);
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
  cli.commands["--init-magnet"] = init_magnet_db;
  cli.commands["-im"] = init_magnet_db;
  cli.commands["--merge-magnet"] = merge_magnet_db;
  cli.commands["-mm"] = merge_magnet_db;
  cli.commands["--search-magnet"] = search_magnet_db;
  cli.commands["-sm"] = search_magnet_db;
  cli.commands["--torrent"] = download_torrent;
  cli.commands["-t"] = download_torrent;
  cli.commands["--magnet"] = download_magnet;
  cli.commands["-m"] = download_magnet;

  return cli.handle(argc, argv);
}

void handle_download(const std::vector<std::shared_ptr<BF::Torrent>>& downloads) {
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
