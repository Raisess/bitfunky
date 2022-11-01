#include <chrono>
#include <thread>
#include "Util.h"

void BF::Util::Sleep(uint16_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
