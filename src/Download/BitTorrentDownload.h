#pragma once

#include <iostream>
#include <libtorrent/add_torrent_params.hpp>
#include "Download.h"

namespace AG {

class BitTorrentDownload : public Download {
public:
  BitTorrentDownload(const std::string& alias, const std::string& uri, const std::string& output);
  ~BitTorrentDownload();

  lt::add_torrent_params get_lt_params() const;

private:
  lt::add_torrent_params lt_torrent_params;
};

}
