#include "TorrentDownload.h"

std::shared_ptr<BF::TorrentDownload> BF::TorrentDownload::CreateFromMagnet(
  const std::string& alias,
  const std::string& magnet_uri,
  const std::string& output
) {
  return std::make_shared<TorrentDownload>(alias, magnet_uri, output, true);
}

std::shared_ptr<BF::TorrentDownload> BF::TorrentDownload::CreateFromTorrent(
  const std::string& alias,
  const std::string& file_path,
  const std::string& output
) {
  return std::make_shared<TorrentDownload>(alias, file_path, output, false);
}

BF::TorrentDownload::TorrentDownload(
  const std::string& alias,
  const std::string& input,
  const std::string& output,
  bool magnet
) : alias(alias), input(input), output(output), magnet(magnet) {
  this->state.status = TorrentDownloadState::Status::CREATED;
}

BF::TorrentDownload::~TorrentDownload() {}

lt::torrent_handle BF::TorrentDownload::get_torrent_handle() const {
  return this->lt_torrent_handle;
}

void BF::TorrentDownload::set_torrent_handle(const lt::torrent_handle& torrent_handle) {
  this->lt_torrent_handle = torrent_handle;
}

const bool BF::TorrentDownload::is_magnet() const {
  return this->magnet;
}

const std::string BF::TorrentDownload::get_alias() const {
  return this->alias;
}

const std::string BF::TorrentDownload::get_input() const {
  return this->input;
}

const std::string BF::TorrentDownload::get_output() const {
  return this->output;
}
