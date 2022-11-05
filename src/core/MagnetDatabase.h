#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../database/SqLite.h"
#include "TorrentDownload.h"

#define DEFAULT_SQLITE_DATABASE "magnet_database.db"
#define DEFAULT_OUTPUT_PATH "./Downloads"

namespace BF {

class MagnetModel {
public:
  MagnetModel(
    const std::string& alias,
    const std::string& magnet_uri,
    const std::string& create_date
  ) : alias(alias), magnet_uri(magnet_uri), create_date(create_date) {}
  ~MagnetModel() {}

  std::string alias;
  std::string magnet_uri;
  std::string create_date;
};

class MagnetDatabase {
public:
  static void Init();
  static void Merge(const std::string& database_path);

  MagnetDatabase();
  ~MagnetDatabase();

  void add(const std::string& alias, const std::string& magnet_uri);
  const MagnetModel find(const std::string& alias);
  const std::vector<MagnetModel> search(const std::string& like);
  std::shared_ptr<BF::TorrentDownload> torrent_from(const std::string& alias, const std::string& output);

private:
  SqLite db;
};

}
