#include "Torrent.h"

std::shared_ptr<BF::Torrent> BF::Torrent::Create(
  const std::string& alias,
  const std::string& input,
  const std::string& output
) {
  return std::make_shared<Torrent>(alias, input, output);
}

const bool BF::Torrent::IsMagnet(const std::string& uri) {
  return uri.substr(0, 8).compare("magnet:?") == 0;
}

BF::Torrent::Torrent(
  const std::string& alias,
  const std::string& input,
  const std::string& output
) : alias(alias), input(input), output(output) {
  this->state.status = TorrentState::Status::CREATED;
}

BF::Torrent::~Torrent() {}

lt::torrent_handle BF::Torrent::get_torrent_handle() const {
  return this->lt_torrent_handle;
}

void BF::Torrent::set_torrent_handle(const lt::torrent_handle& torrent_handle) {
  this->lt_torrent_handle = torrent_handle;
}

const bool BF::Torrent::is_magnet() const {
  return Torrent::IsMagnet(this->input);
}

const std::string BF::Torrent::get_alias() const {
  return this->alias;
}

const std::string BF::Torrent::get_input() const {
  return this->input;
}

const std::string BF::Torrent::get_output() const {
  return this->output;
}

const std::string BF::Torrent::serialize() const {
  return "Torrent:"
    "\n\talias:" + this->alias +
    "\n\tinput:" + this->input +
    "\n\toutput:" + this->output +
    "\n" + this->state.serialize() + "\n";
}

const std::string BF::TorrentState::serialize() const {
  return "TorrentState:"
    "\n\tstatus:" + std::to_string(this->status) +
    "\n\tprogress:" + std::to_string(unsigned(this->progress)) +
    "\n\tpeers:" + std::to_string(unsigned(this->peers)) +
    "\n\tdownload_rate:" + std::to_string(unsigned(this->download_rate)) +
    "\n\ttotal_downloaded:" + std::to_string(unsigned(this->total_downloaded)) + "\n";
}
