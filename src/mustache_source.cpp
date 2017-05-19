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
 * File:   source.cpp
 * Author: alex
 * 
 * Created on October 28, 2016, 8:39 PM
 */

#include "staticlib/mustache/source.hpp"

#include <array>
#include <map>
#include <vector>

#include "mstch/mstch.hpp"

#include "staticlib/config.hpp"
#include "staticlib/io.hpp"
#include "staticlib/pimpl/forward_macros.hpp"
#include "staticlib/utils.hpp"

#include "mstch_utils.hpp"

namespace staticlib {
namespace mustache {

namespace { // anonymous

using partmap_type = const std::map<std::string, std::string>&;

} //namespace

class source::impl : public sl::pimpl::object::impl {
    mstch::renderer renderer;

public:

    ~impl() STATICLIB_NOEXCEPT { }

    impl(const std::string& mustache_file_path, const sl::json::value& json,
            const std::map<std::string, std::string>& partials) try :
        renderer(utils::read_file_to_string(mustache_file_path), utils::create_mstch_node(json), partials) {
    } catch (const std::exception& e) {
        throw mustache_exception(TRACEMSG(e.what() +
                "\nError processing mustache template: [" + mustache_file_path + "]" +
                " with values: [" + json.dumps() + "]"));
    }

    std::streamsize read(source&, sl::io::span<char> span) {
        return renderer.read(span.data(), span.size_signed());
    }   

};
PIMPL_FORWARD_CONSTRUCTOR(source, (const std::string&)(const sl::json::value&)(partmap_type), (), mustache_exception)
PIMPL_FORWARD_METHOD(source, std::streamsize, read, (sl::io::span<char>), (), mustache_exception)
    
} // namespace
}
