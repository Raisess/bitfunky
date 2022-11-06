#include <libtorrent/bencode.hpp>
#include <libtorrent/create_torrent.hpp>
#include <libtorrent/file_storage.hpp>
#include "../util/File.h"
#include "TorrentMaker.h"

BF::Torrent BF::TorrentMaker::Make(const TorrentMaker& maker) {
  lt::file_storage fs;
  lt::add_files(fs, maker.file_path);

  lt::create_torrent torrent(fs);
  torrent.set_creator(maker.creator.c_str());

  for (auto& seed : maker.seeds) {
    torrent.add_url_seed(seed);
  }
  for (auto& tracker : maker.trackers) {
    torrent.add_tracker(tracker);
  }

  lt::set_piece_hashes(torrent, "");

  std::vector<char> t_vec;
  lt::bencode(std::back_inserter(t_vec), torrent.generate());

  const auto output_path = maker.name + ".torrent";
  BF::File file(output_path);
  file.write(std::string(t_vec.data()));

  return BF::Torrent(maker.name, output_path, ".");
}

BF::TorrentMaker::TorrentMaker(
  const std::string& creator,
  const std::string& name,
  const std::string& file_path
) : creator(creator), name(name), file_path(file_path) {}

BF::TorrentMaker::~TorrentMaker() {}

void BF::TorrentMaker::add_seed(const std::string& seed) {
  this->seeds.push_back(seed);
}

void BF::TorrentMaker::add_tracker(const std::string& tracker) {
  this->trackers.push_back(tracker);
}
