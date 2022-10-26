#pragma once

#include <iostream>
#include <libtorrent/add_torrent_params.hpp>

namespace AG {

class TorrentDownloadState {
public:
  enum Status {
    FAILED = 0,
    CREATED,
    ACTIVE,
    PAUSED,
    FINISHED,
    SEEDING, // BitTorrent only
  };

  Status status;
  uint8_t progress = 0; // in percent
  uint16_t peers = 0;
  uint64_t download_rate = 0; // in kB
  uint64_t total_downloaded = 0; // in kB
};

class TorrentDownload {
public:
  TorrentDownloadState state;

  TorrentDownload(const std::string& alias, const std::string& magnet_uri, const std::string& output);
  ~TorrentDownload();

  const std::string get_alias() const;
  const std::string get_magnet_uri() const;
  const std::string get_output() const;

  lt::add_torrent_params get_add_torrent_params() const;

private:
  std::string alias;
  std::string magnet_uri;
  std::string output;

  lt::add_torrent_params lt_add_torrent_params;
};

}
