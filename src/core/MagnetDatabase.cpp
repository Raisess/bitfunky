#include "MagnetDatabase.h"

void BF::MagnetDatabase::Init(const std::string& database_path) {
  SqLite db(database_path);
  db.run(
    "CREATE TABLE magnets("
    "  alias       VARCHAR(255),"
    "  magnet_uri  TEXT        UNIQUE,"
    "  create_date VARCHAR(25) DEFAULT(datetime('now'))"
    ");"
  );
}

void BF::MagnetDatabase::Merge(
  const std::string& from_database_path,
  const std::string& to_database_path
) {
  SqLite db(to_database_path);
  SqLite target_db(from_database_path);
  auto result = target_db.run("SELECT alias, magnet_uri, create_date FROM magnets");

  std::string values_sql;
  for (size_t i = 0; i < result->data.size(); i += 3) {
    values_sql += "(\"" + result->data[i]     + "\"," +
                  "\"" + result->data[i + 1] + "\"," +
                  "\"" + result->data[i + 2] + "\"" +
                  (i == (result->data.size() - 3) ? ");" : "),");
  }

  db.run("INSERT INTO magnets(alias, magnet_uri, create_date) VALUES" + values_sql);
}

BF::MagnetDatabase::MagnetDatabase(const std::string& database_path)
  : db(database_path) {}

BF::MagnetDatabase::~MagnetDatabase() {}

void BF::MagnetDatabase::add(const std::string& alias, const std::string& magnet_uri) {
  const std::string values = "\"" + alias + "\",\"" + magnet_uri + "\"";
  this->db.run("INSERT INTO magnets(alias, magnet_uri) VALUES(" + values + ");");
}

const BF::MagnetModel BF::MagnetDatabase::find(const std::string& alias) {
  const std::string where = "alias = \"" + alias + "\"";
  auto result = this->db.run(
    "SELECT alias, magnet_uri, create_date FROM magnets WHERE " + where + " LIMIT 1;"
  );

  if (result->data.empty()) {
    std::cerr << "Magnet not found" << std::endl;
    exit(1);
  }

  return MagnetModel(result->data[0], result->data[1], result->data[2]);
}

const std::vector<BF::MagnetModel> BF::MagnetDatabase::search(const std::string& like) {
  const std::string where = "alias LIKE \"%" + like + "%\"";
  auto result = this->db.run(
    "SELECT alias, magnet_uri, create_date FROM magnets WHERE " + where + " LIMIT " + std::to_string(DEFAULT_SEARCH_LIMIT) + ";"
  );

  std::vector<BF::MagnetModel> model_vec;
  for (size_t i = 0; i < result->data.size(); i += 3) {
    model_vec.emplace_back(result->data[i], result->data[i + 1], result->data[i + 2]);
  }

  return model_vec;
}
