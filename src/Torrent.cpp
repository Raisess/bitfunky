#include <libtorrent/magnet_uri.hpp>
#include "Torrent.h"

std::shared_ptr<AG::Torrent> AG::Torrent::Create(
  const std::string& alias,
  const std::string& magnet_uri
) {
  return std::make_shared<Torrent>(alias, magnet_uri, ".");
}

std::shared_ptr<AG::Torrent> AG::Torrent::Create(
  const std::string& alias,
  const std::string& magnet_uri,
  const std::string& output
) {
  return std::make_shared<Torrent>(alias, magnet_uri, output);
}

AG::Torrent::Torrent(const std::string& alias, const std::string& magnet_uri, const std::string& output)
  : alias(alias), magnet_uri(magnet_uri), output(output) {
  this->status.state = TorrentStatus::State::CREATED;
  this->lt_attach_params = lt::parse_magnet_uri(magnet_uri);
  this->lt_attach_params.save_path = output;
}

AG::Torrent::~Torrent() {}

const std::string AG::Torrent::get_alias() const {
  return this->alias;
}

const std::string AG::Torrent::get_magnet_uri() const {
  return this->magnet_uri;
}

const std::string AG::Torrent::get_output() const {
  return this->output;
}

lt::add_torrent_params AG::Torrent::get_lt_params() const {
  return this->lt_attach_params;
}
