#pragma once

#include <memory>
#include <vector>
#include <libtorrent/session.hpp>
#include "../Download/BitTorrentDownload.h"
#include "../Session.h"

namespace AG {

class BitTorrentSession : public Session<BitTorrentDownload> {
public:
  BitTorrentSession();
  ~BitTorrentSession();

  void handle(const std::shared_ptr<BitTorrentDownload>&) final override;

private:
  std::unique_ptr<lt::session> lt_session = nullptr;
};

}
