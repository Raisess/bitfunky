#include "Torrent.h"

std::shared_ptr<AG::Torrent> AG::Torrent::Create(const std::string& magnet_uri) {
  return std::make_shared<Torrent>(magnet_uri, ".");
}

std::shared_ptr<AG::Torrent> AG::Torrent::Create(const std::string& magnet_uri, const std::string& output) {
  return std::make_shared<Torrent>(magnet_uri, output);
}

AG::Torrent::Torrent(const std::string& magnet_uri, const std::string& output)
  : magnet_uri(magnet_uri), output(output) {}

AG::Torrent::~Torrent() {}

const std::string AG::Torrent::get_magnet_uri() const {
  return this->magnet_uri;
}

const std::string AG::Torrent::get_output() const {
  return this->output;
}
