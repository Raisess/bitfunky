#include "Session.h"

AG::Session::Session() {}

AG::Session::~Session() {}

void AG::Session::push(const std::shared_ptr<Torrent>& torrent) {
  this->queue.push_back(torrent);
}

void AG::Session::push(const std::vector<std::shared_ptr<Torrent>>& torrents) {
  for (auto torrent : torrents) {
    this->push(torrent);
  }
}

void AG::Session::pop() {
  this->queue.pop_back();
}

int AG::Session::handle() {
  try {
    return 0;
  } catch (std::exception& err) {
    return 1;
  }
}
