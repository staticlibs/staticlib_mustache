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
 * File:   source_test.cpp
 * Author: alex
 *
 * Created on October 28, 2016, 9:23 PM
 */

#include "staticlib/mustache/source.hpp"

#include <array>
#include <iostream>

#include "staticlib/config/assert.hpp"
#include "staticlib/io.hpp"
#include "staticlib/json.hpp"
#include "staticlib/tinydir.hpp"
#include "staticlib/utils.hpp"

const std::string tmp_file_name = "source_test.mustache";

void test_render() {
    std::string text = "{{>header}}:\n{{#names}}Hi {{name}}!\n{{/names}}";
    {
        auto fd = sl::tinydir::file_sink(tmp_file_name);
        auto src = sl::io::string_source(text);        
        sl::io::copy_all(src, fd);
    }
    auto values = sl::json::loads(R"({
    "names": [
        {"name": "Chris"},
        {"name": "Mark"},
        {"name": "Scott"}
    ]
})");
    std::map<std::string, std::string> partials = {{"header", "Behold"}};
    auto ms = sl::mustache::source(tmp_file_name, values, partials);
    auto sink = sl::io::string_sink();
    sl::io::copy_all(ms, sink);
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

