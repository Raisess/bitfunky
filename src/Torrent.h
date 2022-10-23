#pragma once

#include <iostream>
#include <memory>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/magnet_uri.hpp>

namespace AG {

class Torrent {
public:
  static std::shared_ptr<Torrent> Create(const std::string& magnet_uri);
  static std::shared_ptr<Torrent> Create(const std::string& magnet_uri, const std::string& output);

  Torrent(const std::string& magnet_uri, const std::string& output);
  ~Torrent();

  const std::string get_magnet_uri() const;
  const std::string get_output() const;

  // libtorrent impl
  lt::add_torrent_params get_attach_params() const;

private:
  std::string magnet_uri;
  std::string output;

  // libtorrent impl
  lt::add_torrent_params lt_attach_params;
};

}
