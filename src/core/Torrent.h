#pragma once

#include <iostream>
#include <memory>
#include <libtorrent/torrent_handle.hpp>

namespace BF {

class TorrentState {
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

  const std::string serialize() const;
};

class Torrent {
public:
  static std::shared_ptr<Torrent> Create(const std::string& alias, const std::string& input, const std::string& output);
  static const bool IsMagnet(const std::string& uri);

  std::unique_ptr<lt::torrent_handle> handler = nullptr;
  TorrentState state;

  Torrent(const std::string& alias, const std::string& input, const std::string& output);
  ~Torrent();

  const bool is_magnet() const;
  const std::string get_alias() const;
  const std::string get_input() const;
  const std::string get_output() const;
  const std::string serialize() const;

private:
  std::string alias;
  std::string input;
  std::string output;
};

}
