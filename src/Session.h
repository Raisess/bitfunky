#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <libtorrent/session.hpp>
#include "Torrent.h"

namespace AG {

class Session {
public:
  Session();
  ~Session();

  void push(const std::shared_ptr<Torrent>&);
  void push(const std::vector<std::shared_ptr<Torrent>>&);
  int handle(const std::function<void(void)>& callback);

private:
  std::vector<std::shared_ptr<Torrent>> queue;

  std::unique_ptr<lt::session> lt_session = nullptr;
};

}
