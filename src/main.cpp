#include <iostream>
#include "Session.h"
#include "Torrent.h"

#define MAGNET_URI ""

int main(int argc, char* argv[]) {
  AG::Session session;

  auto torrent = AG::Torrent::Create(MAGNET_URI);
  session.push(torrent);

  return session.handle();
}
