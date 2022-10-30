#include "TorrentDownload.h"

std::shared_ptr<BF::TorrentDownload> BF::TorrentDownload::Create(
  const std::string& alias,
  const std::string& input,
  const std::string& output
) {
  return std::make_shared<TorrentDownload>(alias, input, output);
}

const bool BF::TorrentDownload::IsMagnet(const std::string& uri) {
  return uri.substr(0, 8).compare("magnet:?") == 0;
}

BF::TorrentDownload::TorrentDownload(
  const std::string& alias,
  const std::string& input,
  const std::string& output
) : alias(alias), input(input), output(output) {
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
  return TorrentDownload::IsMagnet(this->input);
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
