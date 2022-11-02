#include "core/TorrentDownload.h"
#include "core/TorrentSession.h"
//#include "core/MagnetDatabase.h"

#define OUTPUT_DIR "./output"

int main(int argc, char* argv[]) {
  /*BF::MagnetDatabase magnet_database;
  auto magnet_uri = magnet_database.find("Sintel - Open Movie");
  std::cout << "magnet_uri: " << magnet_uri << std::endl;
  return 0;*/

  auto torrent_list = {
    BF::TorrentDownload::Create(
      "Sintel - Open Movie",
      "magnet:?xt=urn:btih:08ada5a7a6183aae1e09d831df6748d566095a10&dn=Sintel&tr=udp%3A%2F%2Fexplodie.org%3A6969&tr=udp%3A%2F%2Ftracker.coppersurfer.tk%3A6969&tr=udp%3A%2F%2Ftracker.empire-js.us%3A1337&tr=udp%3A%2F%2Ftracker.leechers-paradise.org%3A6969&tr=udp%3A%2F%2Ftracker.opentrackr.org%3A1337&tr=wss%3A%2F%2Ftracker.btorrent.xyz&tr=wss%3A%2F%2Ftracker.fastcast.nz&tr=wss%3A%2F%2Ftracker.openwebtorrent.com&ws=https%3A%2F%2Fwebtorrent.io%2Ftorrents%2F&xs=https%3A%2F%2Fwebtorrent.io%2Ftorrents%2Fsintel.torrent",
      OUTPUT_DIR
    ),
    BF::TorrentDownload::Create(
      "Leaves of Grass - by Walt Whitman",
      "magnet:?xt=urn:btih:d2474e86c95b19b8bcfdb92bc12c9d44667cfa36&dn=Leaves+of+Grass+by+Walt+Whitman.epub&tr=udp%3A%2F%2Ftracker.example4.com%3A80&tr=udp%3A%2F%2Ftracker.example5.com%3A80&tr=udp%3A%2F%2Ftracker.example3.com%3A6969&tr=udp%3A%2F%2Ftracker.example2.com%3A80&tr=udp%3A%2F%2Ftracker.example1.com%3A1337",
      OUTPUT_DIR
    )
  };

  BF::TorrentSession session;
  session.push_download(torrent_list);
  session.loop([]() {});
  session.save_info();

  return 0;
}
