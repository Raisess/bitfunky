#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <libtorrent/session.hpp>
#include "../File/BitTorrentFile.h"
#include "Session.h"

namespace AG {

class BitTorrentSession : public Session<BitTorrentFile> {
public:
  BitTorrentSession();
  ~BitTorrentSession();

  void push(const std::shared_ptr<BitTorrentFile>&) final override;
  void push(const std::vector<std::shared_ptr<BitTorrentFile>>&) final override;
  int handle(const std::function<void(void)>& callback) final override;

private:
  std::unique_ptr<lt::session> lt_session = nullptr;
};

}
