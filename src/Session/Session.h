#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace AG {

template <typename Download>
class Session {
public:
  Session() {}
  ~Session() {}

  virtual void push_download(const std::shared_ptr<Download>&) {}
  virtual void push_download(const std::vector<std::shared_ptr<Download>>&) {}
  virtual void handle(const std::function<void(void)>& callback) {}

protected:
  std::vector<std::shared_ptr<Download>> queue;
};

}
