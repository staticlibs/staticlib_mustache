#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <ios>

#include "mstch/mstch_node.hpp"

namespace mstch {

struct config {
  static std::function<std::string(const std::string&)> escape;
};

using object = internal::object_t<node>;
using lambda = internal::lambda_t<node>;
using map = std::map<const std::string, node>;
using array = std::vector<node>;

std::string render(
    const std::string& tmplt,
    const node& root,
    const std::map<std::string,std::string>& partials =
        std::map<std::string,std::string>());

class renderer {
    class impl;
    std::unique_ptr<renderer::impl> pimpl;
    
public:    
    ~renderer();
    renderer(const renderer&) = delete;
    renderer(renderer&& other);
    renderer& operator=(const renderer&) = delete;
    renderer& operator=(renderer&& other);

    renderer(
        std::string tmplt,
        node root,
        const std::map<std::string, std::string>& partials =
            std::map<std::string, std::string>());
    
    std::streamsize read(char* buffer, std::streamsize length);
};

}
