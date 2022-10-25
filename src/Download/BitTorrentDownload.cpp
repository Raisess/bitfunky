#include <libtorrent/magnet_uri.hpp>
#include "BitTorrentDownload.h"

AG::BitTorrentDownload::BitTorrentDownload(const std::string& alias, const std::string& magnet_uri, const std::string& output)
  : Download(alias, magnet_uri, output) {
  this->state.status = DownloadState::Status::CREATED;
  this->lt_torrent_params = lt::parse_magnet_uri(this->get_uri());
  this->lt_torrent_params.save_path = this->get_output();
}

AG::BitTorrentDownload::~BitTorrentDownload() {}

lt::add_torrent_params AG::BitTorrentDownload::get_lt_params() const {
  return this->lt_torrent_params;
}
