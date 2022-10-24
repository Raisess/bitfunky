#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <libtorrent/session.hpp>
#include "../Download/BitTorrentDownload.h"
#include "Session.h"

namespace AG {

class BitTorrentSession : public Session<BitTorrentDownload> {
public:
  BitTorrentSession();
  ~BitTorrentSession();

  void push(const std::shared_ptr<BitTorrentDownload>&) final override;
  void push(const std::vector<std::shared_ptr<BitTorrentDownload>>&) final override;
  int handle(const std::function<void(void)>& callback) final override;

private:
  std::unique_ptr<lt::session> lt_session = nullptr;
};

}
