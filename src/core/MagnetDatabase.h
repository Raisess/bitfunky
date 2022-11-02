#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../database/SqLite.h"
#include "TorrentDownload.h"

#define DEFAULT_SQLITE_DATABASE "magnet_database.db"
#define DEFAULT_OUTPUT_PATH "./Downloads"

namespace BF {

class MagnetDatabase {
public:
  static void Init();
  static void Download(const std::string& ftp_server_uri);

  MagnetDatabase();
  ~MagnetDatabase();

  void add(const std::string& alias, const std::string& magnet_uri);
  const std::string find(const std::string& alias);
  const std::vector<std::string> search(const std::string& like);
  std::shared_ptr<BF::TorrentDownload> torrent_from(const std::string& alias, const std::string& output);

private:
  SqLite db;
};

}
