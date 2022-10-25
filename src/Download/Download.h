#pragma once

#include <cstdint>
#include <iostream>
#include <memory>

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
  uint8_t progress = 0;
  uint16_t peers = 0;
  uint32_t download_rate = 0;
  uint32_t total_downloaded = 0;
};

template <typename T>
class Download {
public:
  static std::shared_ptr<T> Create(
    const std::string& alias,
    const std::string& uri
  ) {
    return std::make_shared<T>(alias, uri, ".");
  }

  static std::shared_ptr<T> Create(
    const std::string& alias,
    const std::string& uri,
    const std::string& output
  ) {
    return std::make_shared<T>(alias, uri, output);
  }

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
