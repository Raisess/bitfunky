#include "Torrent.h"

std::shared_ptr<AG::Torrent> AG::Torrent::Create(const std::string& magnet_uri) {
  return std::make_shared<Torrent>(magnet_uri, ".");
}

std::shared_ptr<AG::Torrent> AG::Torrent::Create(
  const std::string& magnet_uri,
  const std::string& output
) {
  return std::make_shared<Torrent>(magnet_uri, output);
}

AG::Torrent::Torrent(const std::string& magnet_uri, const std::string& output)
  : magnet_uri(magnet_uri), output(output) {
  this->lt_attach_params = lt::parse_magnet_uri(magnet_uri);
  this->lt_attach_params.save_path = output;
}

AG::Torrent::~Torrent() {}

const std::string AG::Torrent::get_magnet_uri() const {
  return this->magnet_uri;
}

const std::string AG::Torrent::get_output() const {
  return this->output;
}

// libtorrent impl
lt::add_torrent_params AG::Torrent::get_attach_params() const {
  return this->lt_attach_params;
}
