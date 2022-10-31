#include <chrono>
#include <csignal>
#include <thread>
#include "Util.h"

static volatile bool keep_running = true;
static void handle_interrupt_signal(int);

void BF::Util::Loop(const std::function<void(void)>& callback, uint16_t interval_ms) {
  signal(SIGINT, handle_interrupt_signal);

  while (keep_running) {
    callback();
    Util::Sleep(interval_ms);
  }
}

void BF::Util::Sleep(uint16_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

static void handle_interrupt_signal(int) {
  keep_running = false;
}
