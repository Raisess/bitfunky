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
  static std::shared_ptr<TorrentDownload> CreateFromMagnet(const std::string& alias, const std::string& magnet_uri, const std::string& output);
  static std::shared_ptr<TorrentDownload> CreateFromTorrent(const std::string& alias, const std::string& file_path, const std::string& output);

  TorrentDownloadState state;

  TorrentDownload(const std::string& alias, const std::string& input, const std::string& output, bool magnet);
  ~TorrentDownload();

  lt::torrent_handle get_torrent_handle() const;
  void set_torrent_handle(const lt::torrent_handle&);

  const bool is_magnet() const;
  const std::string get_alias() const;
  const std::string get_input() const;
  const std::string get_output() const;

private:
  std::string alias;
  std::string input;
  std::string output;
  bool magnet;

  lt::torrent_handle lt_torrent_handle;
};

}
