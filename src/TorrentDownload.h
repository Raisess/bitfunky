#pragma once

#include <iostream>
#include <memory>
#include <libtorrent/torrent_handle.hpp>

namespace BF {

class TorrentDownloadState {
public:
  enum Status {
    FAILED = 0,
    CREATED,
    ACTIVE,
    PAUSED,
    FINISHED,
    SEEDING,
  };

  Status status;
  uint8_t progress = 0; // in percent
  uint16_t peers = 0;
  uint64_t download_rate = 0; // in kB
  uint64_t total_downloaded = 0; // in kB
};

class TorrentDownload {
public:
  static std::shared_ptr<TorrentDownload> Create(const std::string& alias, const std::string& magnet_uri);
  static std::shared_ptr<TorrentDownload> Create(const std::string& alias, const std::string& magnet_uri, const std::string& output);

  TorrentDownloadState state;

  TorrentDownload(const std::string& alias, const std::string& magnet_uri, const std::string& output);
  ~TorrentDownload();

  lt::torrent_handle get_torrent_handle() const;
  void set_torrent_handle(const lt::torrent_handle&);

  const std::string get_alias() const;
  const std::string get_magnet_uri() const;
  const std::string get_output() const;

private:
  std::string alias;
  std::string magnet_uri;
  std::string output;

  lt::torrent_handle lt_torrent_handle;
};

}