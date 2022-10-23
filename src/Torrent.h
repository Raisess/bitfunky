#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <libtorrent/add_torrent_params.hpp>
#include <libtorrent/magnet_uri.hpp>

namespace AG {

class TorrentStatus {
public:
  enum Flag {
    CREATED = 0,
    ACTIVE,
    PAUSED,
    FINISHED,
    FAILED,
  };

  Flag flag;
  uint8_t progress = 0;
  uint16_t peers = 0;
  uint16_t download_rate = 0;
};

class Torrent {
public:
  static std::shared_ptr<Torrent> Create(
    const std::string& alias,
    const std::string& magnet_uri
  );
  static std::shared_ptr<Torrent> Create(
    const std::string& alias,
    const std::string& magnet_uri,
    const std::string& output
  );

  TorrentStatus status;

  Torrent(const std::string& alias, const std::string& magnet_uri, const std::string& output);
  ~Torrent();

  const std::string get_alias() const;
  const std::string get_magnet_uri() const;
  const std::string get_output() const;

  // libtorrent impl
  lt::add_torrent_params get_lt_params() const;

private:
  std::string alias;
  std::string magnet_uri;
  std::string output;

  // libtorrent impl
  lt::add_torrent_params lt_attach_params;
};

}
