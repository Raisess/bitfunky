#pragma once

#include <cstdint>
#include <iostream>
#include <libtorrent/add_torrent_params.hpp>
#include "File.h"

namespace AG {

class BitTorrentFileStatus {
public:
  enum State {
    CREATED = 0,
    ACTIVE,
    PAUSED,
    FINISHED,
    SEEDING,
    FAILED,
  };

  State state;
  uint8_t progress = 0;
  uint16_t peers = 0;
  uint32_t download_rate = 0;
  uint32_t total_downloaded = 0;
};

class BitTorrentFile : public File<BitTorrentFile> {
public:
  BitTorrentFileStatus status;

  BitTorrentFile(const std::string& alias, const std::string& uri, const std::string& output);
  ~BitTorrentFile();

  lt::add_torrent_params get_lt_params() const;

private:
  lt::add_torrent_params lt_attach_params;
};

}
