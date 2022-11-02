#include "MagnetDatabase.h"

void BF::MagnetDatabase::Init() {
  SqLite db(DEFAULT_SQLITE_DATABASE);
  db.run(
    "CREATE TABLE magnet("
    " id         INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
    " alias      VARCHAR(255),"
    " magnet_uri TEXT UNIQUE"
    ");"
  );
}

void BF::MagnetDatabase::Download(const std::string& ftp_server_uri) {
  // TODO: curl from ftp server
}

BF::MagnetDatabase::MagnetDatabase() : db(DEFAULT_SQLITE_DATABASE) {}

BF::MagnetDatabase::~MagnetDatabase() {}

void BF::MagnetDatabase::add(const std::string& alias, const std::string& magnet_uri) {
  const std::string values = "\"" + alias + "\",\"" + magnet_uri + "\"";
  this->db.run("INSERT INTO magnet(alias, magnet_uri) VALUES(" + values + ");");
}

const std::string BF::MagnetDatabase::find(const std::string& alias) {
  const std::string where = "alias = \"" + alias + "\" OR id = \"" + alias + "\"";
  auto result = this->db.run("SELECT magnet_uri FROM magnet WHERE " + where + ";");
  return result->data[0];
}

const std::vector<std::string> BF::MagnetDatabase::search(const std::string& like) {
  const std::string where = "alias LIKE %" + like + "%";
  auto result = this->db.run("SELECT magnet_uri FROM magnet WHERE " + where + ";");
  return result->data;
}

std::shared_ptr<BF::TorrentDownload> BF::MagnetDatabase::torrent_from(
  const std::string& alias,
  const std::string& output = DEFAULT_OUTPUT_PATH
) {
  const auto magnet_uri = this->find(alias);
  return BF::TorrentDownload::Create(alias, magnet_uri, output);
}
