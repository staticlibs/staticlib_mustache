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
#define	STATICLIB_MUSTACHE_MSTCH_UTILS_HPP

#include "mstch/mstch.hpp"

#include "staticlib/json.hpp"

#include "staticlib/mustache/mustache_exception.hpp"

namespace staticlib {
namespace mustache {
namespace utils {

mstch::node create_mstch_node(const sl::json::value& value);

std::string read_file_to_string(const std::string& path);

} // namespace
}
}

#endif	/* STATICLIB_MUSTACHE_MSTCH_UTILS_HPP */

