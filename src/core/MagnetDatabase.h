#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../database/SqLite.h"
#include "../util/Util.h"

#define DEFAULT_SQLITE_DATABASE() BF::Util::Env("HOME") + "/.magnet_database.db"

namespace BF {

class MagnetModel {
public:
  std::string alias;
  std::string magnet_uri;
  std::string create_date;

  MagnetModel(
    const std::string& alias,
    const std::string& magnet_uri,
    const std::string& create_date
  ) : alias(alias), magnet_uri(magnet_uri), create_date(create_date) {}
  ~MagnetModel() {}
};

class MagnetDatabase {
public:
  static void Init(const std::string& database_path = DEFAULT_SQLITE_DATABASE());
  static void Merge(
    const std::string& from_database_path,
    const std::string& to_database_path = DEFAULT_SQLITE_DATABASE()
  );

  MagnetDatabase(const std::string& database_path = DEFAULT_SQLITE_DATABASE());
  ~MagnetDatabase();

  void add(const std::string& alias, const std::string& magnet_uri);
  const MagnetModel find(const std::string& alias);
  const std::vector<MagnetModel> search(const std::string& like);

private:
  SqLite db;
};

}
