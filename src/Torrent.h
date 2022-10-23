#pragma once

#include <iostream>
#include <memory>

namespace AG {

class Torrent {
public:
  static std::shared_ptr<Torrent> Create(const std::string& magnet_uri);
  static std::shared_ptr<Torrent> Create(const std::string& magnet_uri, const std::string& output);

  Torrent(const std::string& magnet_uri, const std::string& output);
  ~Torrent();

  const std::string get_magnet_uri() const;
  const std::string get_output() const;

private:
  std::string magnet_uri;
  std::string output;
};

}
