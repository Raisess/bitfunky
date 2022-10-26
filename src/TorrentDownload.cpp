#include <libtorrent/magnet_uri.hpp>
#include "TorrentDownload.h"

std::shared_ptr<AG::TorrentDownload> AG::TorrentDownload::Create(const std::string& alias, const std::string& magnet_uri) {
  return std::make_shared<TorrentDownload>(alias, magnet_uri, ".");
}

std::shared_ptr<AG::TorrentDownload> AG::TorrentDownload::Create(
  const std::string& alias,
  const std::string& magnet_uri,
  const std::string& output
) {
  return std::make_shared<TorrentDownload>(alias, magnet_uri, output);
}

AG::TorrentDownload::TorrentDownload(
  const std::string& alias,
  const std::string& magnet_uri,
  const std::string& output
) : alias(alias), magnet_uri(magnet_uri), output(output) {
  this->state.status = TorrentDownloadState::Status::CREATED;
  this->lt_add_torrent_params = lt::parse_magnet_uri(magnet_uri);
  this->lt_add_torrent_params.save_path = output;
}

AG::TorrentDownload::~TorrentDownload() {}

const std::string AG::TorrentDownload::get_alias() const {
  return this->alias;
}

const std::string AG::TorrentDownload::get_magnet_uri() const {
  return this->magnet_uri;
}

const std::string AG::TorrentDownload::get_output() const {
  return this->output;
}

lt::add_torrent_params AG::TorrentDownload::get_add_torrent_params() const {
  return this->lt_add_torrent_params;
}
