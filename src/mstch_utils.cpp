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
 * File:   mstch_utils.cpp
 * Author: alex
 * 
 * Created on October 28, 2016, 8:52 PM
 */

#include "mstch_utils.hpp"

#include "staticlib/config.hpp"
#include "staticlib/io.hpp"
#include "staticlib/tinydir.hpp"

namespace staticlib {
namespace mustache {
namespace utils {

namespace { // anonymous

namespace sc = staticlib::config;
namespace si = staticlib::io;
namespace ss = staticlib::serialization;
namespace st = staticlib::tinydir;

mstch::node create_map(const ss::json_value& value) {
    std::map<const std::string, mstch::node> map;
    for (const auto& fi : value.as_object()) {
        map.insert({fi.name(), create_mstch_node(fi.value())});
    }
    return mstch::node(std::move(map));
}

mstch::node create_array(const ss::json_value& value) {
    std::vector<mstch::node> array;
    for (const auto& va : value.as_array()) {
        array.emplace_back(create_mstch_node(va));
    }
    return mstch::node(std::move(array));
}

} // namespace

mstch::node create_mstch_node(const ss::json_value& value) {
    switch (value.type()) {
    case (ss::json_type::nullt): return mstch::node();
    case (ss::json_type::object): return create_map(value);
    case (ss::json_type::array): return create_array(value);
    case (ss::json_type::string): return mstch::node(value.as_string());
    case (ss::json_type::integer): return mstch::node(static_cast<int> (value.as_int64()));
    case (ss::json_type::real): return mstch::node(value.as_double());
    case (ss::json_type::boolean): return mstch::node(value.as_bool());
    default: throw mustache_exception(TRACEMSG(
                "Unsupported JSON type:[" + sc::to_string(static_cast<char> (value.type())) + "]"));
    }
}

std::string read_file_to_string(const std::string& path) {
    auto fd = st::file_source(path);
    std::array<char, 4096> buf;
    si::string_sink sink{};
    si::copy_all(fd, sink, buf);
    return std::move(sink.get_string());
}    

} // namespace
}
}
