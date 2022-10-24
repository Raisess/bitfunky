#pragma once

#include <iostream>
#include <memory>

namespace AG {

template <typename T>
class File {
public:
  static std::shared_ptr<T> Create(
    const std::string& alias,
    const std::string& uri
  ) {
    return std::make_shared<T>(alias, uri, ".");
  }

  static std::shared_ptr<T> Create(
    const std::string& alias,
    const std::string& uri,
    const std::string& output
  ) {
    return std::make_shared<T>(alias, uri, output);
  }

  File(const std::string& alias, const std::string& uri, const std::string& output)
    : alias(alias), uri(uri), output(output) {}
  ~File() {}

  const std::string get_alias() const {
    return this->alias;
  }

  const std::string get_uri() const {
    return this->uri;
  }

  const std::string get_output() const {
    return this->output;
  }

private:
  std::string alias;
  std::string uri;
  std::string output;
};

}
