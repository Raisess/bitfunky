#include "SqLite.h"

BF::SqLite::SqLite(const std::string& file) {
  if (sqlite3_open(file.c_str(), &this->db)) {
    std::cerr << "Failed to open database at: " << file << std::endl;
    exit(1);
  }
}

BF::SqLite::~SqLite() {
  sqlite3_close(this->db);
}

static int callback(void* mem, int argc, char* argv[], char**) {
  ((BF::QueryResult*) mem)->count = argc;
  for (int i = 0; i < argc; i++) {
    ((BF::QueryResult*) mem)->data.push_back(argv[i] ? argv[i] : "NULL");
  }
  return 0;
}

std::shared_ptr<BF::QueryResult> BF::SqLite::run(const std::string& sql) {
  char* err_msg = 0;
  auto query_result = std::make_shared<QueryResult>();
  auto res = sqlite3_exec(this->db, sql.c_str(), callback, (void*) query_result.get(), &err_msg);

  if (res != SQLITE_OK) {
    std::cerr << "Query failed" << std::endl;
    sqlite3_free(err_msg);
  }

  return query_result;
}
