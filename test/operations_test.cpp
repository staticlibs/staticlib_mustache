/* 
 * File:   operations_test.cpp
 * Author: alex
 *
 * Created on October 28, 2016, 9:23 PM
 */

#include "staticlib/mustache/operations.hpp"

#include <array>
#include <iostream>

#include "staticlib/config/assert.hpp"
#include "staticlib/io.hpp"
#include "staticlib/serialization.hpp"
#include "staticlib/utils.hpp"

namespace si = staticlib::io;
namespace sm = staticlib::mustache;
namespace ss = staticlib::serialization;
namespace su = staticlib::utils;

void test_render() {
    std::string text = "{{>header}}:\n{{#names}}Hi {{name}}!\n{{/names}}";
    std::vector<ss::JsonValue> names;
    ss::JsonValue values = ss::load_json_from_string(R"({
    "names": [
        {"name": "Chris"},
        {"name": "Mark"},
        {"name": "Scott"}
    ]
})");
    {
        auto fd = su::FileDescriptor("header.mustache", 'w');
        auto src = si::string_source("Behold");
        std::array<char, 4096> buf;
        si::copy_all(src, fd, buf.data(), buf.size());
    }
    std::map<std::string, std::string> partials = sm::load_partials(".");
    std::string res = sm::render_string(text, values, partials);
    slassert("Behold:\nHi Chris!\nHi Mark!\nHi Scott!\n" == res);
}

int main() {
    try {
        test_render();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

