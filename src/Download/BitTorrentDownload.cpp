#include <libtorrent/magnet_uri.hpp>
#include "BitTorrentDownload.h"

AG::BitTorrentDownload::BitTorrentDownload(const std::string& alias, const std::string& uri, const std::string& output)
  : Download(alias, uri, output) {
  this->status.state = BitTorrentDownloadStatus::State::CREATED;
  this->lt_attach_params = lt::parse_magnet_uri(uri);
  this->lt_attach_params.save_path = output;
}

AG::BitTorrentDownload::~BitTorrentDownload() {}

lt::add_torrent_params AG::BitTorrentDownload::get_lt_params() const {
  return this->lt_attach_params;
}
