#pragma once

#include <iostream>
#include <vector>
#include "Torrent.h"

namespace BF {

class TorrentMaker {
public:
  static Torrent Make(const TorrentMaker&);
  static const std::string FromTorrentToMagnet(const std::string& file_path);

  // Only accept directories paths
  TorrentMaker(
    const std::string& creator,
    const std::string& name,
    const std::string& file_path
  );
  ~TorrentMaker();

  void add_seed(const std::string&);
  void add_tracker(const std::string&);

private:
  std::string creator;
  std::string name;
  std::string file_path;
  std::vector<std::string> seeds;
  std::vector<std::string> trackers;
};

}
