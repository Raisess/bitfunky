#pragma once

#include <memory>
#include <vector>
#include "Torrent.h"

namespace AG {

class Session {
public:
  Session();
  ~Session();

  void push(const std::shared_ptr<Torrent>&);
  void push(const std::vector<std::shared_ptr<Torrent>>&);
  void pop();
  int handle();

private:
  std::vector<std::shared_ptr<Torrent>> queue;
};

}
