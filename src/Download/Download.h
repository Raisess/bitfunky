#pragma once

#include <cstdint>
#include <iostream>

namespace AG {

class DownloadState {
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
  uint64_t download_rate = 0; // in kB
  uint64_t total_downloaded = 0; // in kB
  uint16_t peers = 0; // BitTorrent only
};

class Download {
public:
  DownloadState state;

  Download(const std::string& alias, const std::string& uri, const std::string& output)
    : alias(alias), uri(uri), output(output) {}
  ~Download() {}

  const std::string get_alias() const {
    return this->alias;
  }

  const std::string get_uri() const {
    return this->uri;
  }

  const std::string get_output() const {
    return this->output;
  }

private:
  std::string alias;
  std::string uri;
  std::string output;
};

}
