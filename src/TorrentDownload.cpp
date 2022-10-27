#include "TorrentDownload.h"

std::shared_ptr<BF::TorrentDownload> BF::TorrentDownload::Create(const std::string& alias, const std::string& magnet_uri) {
  return std::make_shared<TorrentDownload>(alias, magnet_uri, ".");
}

std::shared_ptr<BF::TorrentDownload> BF::TorrentDownload::Create(
  const std::string& alias,
  const std::string& magnet_uri,
  const std::string& output
) {
  return std::make_shared<TorrentDownload>(alias, magnet_uri, output);
}

BF::TorrentDownload::TorrentDownload(
  const std::string& alias,
  const std::string& magnet_uri,
  const std::string& output
) : alias(alias), magnet_uri(magnet_uri), output(output) {
  this->state.status = TorrentDownloadState::Status::CREATED;
}

BF::TorrentDownload::~TorrentDownload() {}

lt::torrent_handle BF::TorrentDownload::get_torrent_handle() const {
  return this->lt_torrent_handle;
}

void BF::TorrentDownload::set_torrent_handle(const lt::torrent_handle& torrent_handle) {
  this->lt_torrent_handle = torrent_handle;
}

const std::string BF::TorrentDownload::get_alias() const {
  return this->alias;
}

const std::string BF::TorrentDownload::get_magnet_uri() const {
  return this->magnet_uri;
}

const std::string BF::TorrentDownload::get_output() const {
  return this->output;
}
