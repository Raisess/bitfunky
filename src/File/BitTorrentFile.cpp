#include <libtorrent/magnet_uri.hpp>
#include "BitTorrentFile.h"

AG::BitTorrentFile::BitTorrentFile(const std::string& alias, const std::string& uri, const std::string& output)
  : File(alias, uri, output) {
  this->status.state = BitTorrentFileStatus::State::CREATED;
  this->lt_attach_params = lt::parse_magnet_uri(uri);
  this->lt_attach_params.save_path = output;
}

AG::BitTorrentFile::~BitTorrentFile() {}

lt::add_torrent_params AG::BitTorrentFile::get_lt_params() const {
  return this->lt_attach_params;
}
