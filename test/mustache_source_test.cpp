/*
 * Copyright 2016, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   mustache_source_test.cpp
 * Author: alex
 *
 * Created on October 28, 2016, 9:23 PM
 */

#include "staticlib/mustache/mustache_source.hpp"

#include <array>
#include <iostream>

#include "staticlib/config/assert.hpp"
#include "staticlib/io.hpp"
#include "staticlib/serialization.hpp"
#include "staticlib/tinydir.hpp"
#include "staticlib/utils.hpp"

namespace si = staticlib::io;
namespace sm = staticlib::mustache;
namespace ss = staticlib::serialization;
namespace st = staticlib::tinydir;
namespace su = staticlib::utils;

const std::string tmp_file_name = "mustache_source_test.mustache";

void test_render() {
    std::array<char, 4096> buf;
    std::string text = "{{>header}}:\n{{#names}}Hi {{name}}!\n{{/names}}";
    {
        auto fd = st::file_sink(tmp_file_name);
        auto src = si::string_source(text);        
        si::copy_all(src, fd, buf);
    }
    ss::json_value values = ss::load_json_from_string(R"({
    "names": [
        {"name": "Chris"},
        {"name": "Mark"},
        {"name": "Scott"}
    ]
})");
    std::map<std::string, std::string> partials = {{"header", "Behold"}};
    auto ms = sm::mustache_source(tmp_file_name, values, partials);
    auto sink = si::string_sink();
    si::copy_all(ms, sink, buf);
    slassert("Behold:\nHi Chris!\nHi Mark!\nHi Scott!\n" == sink.get_string());
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

