#pragma once

#include <cstdint>
#include <iostream>
#include <libtorrent/add_torrent_params.hpp>
#include "Download.h"

namespace AG {

class BitTorrentDownloadStatus {
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

class BitTorrentDownload : public Download<BitTorrentDownload> {
public:
  BitTorrentDownloadStatus status;

  BitTorrentDownload(const std::string& alias, const std::string& uri, const std::string& output);
  ~BitTorrentDownload();

  lt::add_torrent_params get_lt_params() const;

private:
  lt::add_torrent_params lt_attach_params;
};

}
