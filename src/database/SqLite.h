#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>
#include <sqlite3.h>

namespace BF {

class QueryResult {
public:
  uint32_t count;
  std::vector<std::string> data;
};

class SqLite {
public:
  SqLite(const std::string& file);
  ~SqLite();

  std::shared_ptr<QueryResult> run(const std::string& sql);

private:
  sqlite3* db;
};

}
