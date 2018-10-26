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
 * File:   mstch_utils.hpp
 * Author: alex
 *
 * Created on October 28, 2016, 8:52 PM
 */

#ifndef STATICLIB_MUSTACHE_MSTCH_UTILS_HPP
#define STATICLIB_MUSTACHE_MSTCH_UTILS_HPP

#include "mstch/mstch.hpp"

#include "staticlib/config.hpp"
#include "staticlib/json.hpp"
#include "staticlib/io.hpp"
#include "staticlib/tinydir.hpp"

#include "staticlib/mustache/mustache_exception.hpp"

namespace staticlib {
namespace mustache {
namespace utils {

// forward decl
inline mstch::node create_mstch_node(const sl::json::value& value);

namespace detail {

inline mstch::node create_map(const sl::json::value& value) {
    std::map<const std::string, mstch::node> map;
    for (const auto& fi : value.as_object()) {
        map.insert({fi.name(), create_mstch_node(fi.val())});
    }
    return mstch::node(std::move(map));
}

inline mstch::node create_array(const sl::json::value& value) {
    std::vector<mstch::node> array;
    for (const auto& va : value.as_array()) {
        array.emplace_back(create_mstch_node(va));
    }
    return mstch::node(std::move(array));
}

} // namespace

inline mstch::node create_mstch_node(const sl::json::value& value) {
    switch (value.json_type()) {
    case (sl::json::type::nullt): return mstch::node();
    case (sl::json::type::object): return detail::create_map(value);
    case (sl::json::type::array): return detail::create_array(value);
    case (sl::json::type::string): return mstch::node(value.as_string());
    case (sl::json::type::integer): return mstch::node(static_cast<int> (value.as_int64()));
    case (sl::json::type::real): return mstch::node(value.as_double());
    case (sl::json::type::boolean): return mstch::node(value.as_bool());
    default: throw mustache_exception(TRACEMSG(
                "Unsupported JSON type:[" + sl::support::to_string(static_cast<char> (value.json_type())) + "]"));
    }
}

inline std::string read_file_to_string(const std::string& path) {
    auto fd = sl::tinydir::file_source(path);
    auto sink = sl::io::string_sink();
    sl::io::copy_all(fd, sink);
    return std::move(sink.get_string());
}

} // namespace
}
}

#endif /* STATICLIB_MUSTACHE_MSTCH_UTILS_HPP */

