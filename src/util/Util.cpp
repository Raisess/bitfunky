#include <chrono>
#include <cstdlib>
#include <thread>
#include "Util.h"

void BF::Util::Sleep(uint16_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

const std::string BF::Util::Env(const std::string& var) {
  return std::string(std::getenv(var.c_str()));
}
