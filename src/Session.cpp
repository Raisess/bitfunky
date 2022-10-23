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
    | lt::alert_category::storage
  );
  this->lt_session = std::make_unique<lt::session>(lt_settings);
}

AG::Session::~Session() {}

void AG::Session::push(const std::shared_ptr<Torrent>& torrent) {
  std::cout << "Torrent added to session: " << torrent->get_magnet_uri() << std::endl;
  this->lt_session->add_torrent(torrent->get_lt_params());
  this->queue.push_back(torrent);
}

void AG::Session::push(const std::vector<std::shared_ptr<Torrent>>& torrents) {
  for (auto torrent : torrents) {
    this->push(torrent);
  }
}

int AG::Session::handle() {
  try {
    while (true) {
      std::vector<lt::alert*> lt_alerts;
      this->lt_session->pop_alerts(&lt_alerts);

      for (auto alert : lt_alerts) {
        // End status check
        if (lt::alert_cast<lt::torrent_finished_alert>(alert)
            || lt::alert_cast<lt::torrent_error_alert>(alert)) {
          break;
        }

        auto state = lt::alert_cast<lt::state_update_alert>(alert);
        if (state) {
          if (state->status.empty()) continue;

          auto status = state->status[0];
          std::cout << "Downloaded: " << status.progress_ppm / 10000 << std::endl;
          std::cout << "Peers: " << status.num_peers << std::endl;
        }
      }

      this->lt_session->post_torrent_updates();
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    std::cout << "Finished!" << std::endl;
    return 0;
  } catch (std::exception& err) {
    std::cerr << "Error: " << err.what() << std::endl;
    return 1;
  }
}
