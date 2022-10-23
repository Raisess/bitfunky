#include <chrono>
#include <iostream>
#include <thread>
#include "Session.h"

AG::Session::Session() {
  lt::settings_pack lt_settings;
  lt_settings.set_int(
    lt::settings_pack::alert_mask,
    lt::alert_category::error
    | lt::alert_category::status
  );
  this->lt_session = std::make_unique<lt::session>(lt_settings);
}

AG::Session::~Session() {}

void AG::Session::push(const std::shared_ptr<Torrent>& torrent) {
  this->lt_session->add_torrent(torrent->get_attach_params());
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
    while (true) {
      std::vector<lt::alert*> lt_alerts;
      this->lt_session->pop_alerts(&lt_alerts);

      for (auto alert : lt_alerts) {
        std::cout << alert->message() << std::endl;

        // End status check
        if (lt::alert_cast<lt::torrent_finished_alert>(alert)
            || lt::alert_cast<lt::torrent_error_alert>(alert)) {
          break;
        }
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "Finished!" << std::endl;
    return 0;
  } catch (std::exception& err) {
    std::cerr << "Error: " << err.what() << std::endl;
    return 1;
  }
}
