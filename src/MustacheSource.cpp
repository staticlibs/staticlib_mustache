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
 * File:   MustacheSource.cpp
 * Author: alex
 * 
 * Created on October 28, 2016, 8:39 PM
 */

#include "staticlib/mustache/MustacheSource.hpp"

#include <array>
#include <map>
#include <vector>

#include "mstch/mstch.hpp"

#include "staticlib/config.hpp"
#include "staticlib/io.hpp"
#include "staticlib/pimpl/pimpl_forward_macros.hpp"
#include "staticlib/utils.hpp"

#include "mstch_utils.hpp"

namespace staticlib {
namespace mustache {

namespace { // anonymous

namespace sc = staticlib::config;
namespace si = staticlib::io;
namespace ss = staticlib::serialization;
namespace su = staticlib::utils;

using partmap_type = const std::map<std::string, std::string>&;

} //namespace

class MustacheSource::Impl : public staticlib::pimpl::PimplObject::Impl {
    mstch::renderer renderer;

public:

    ~Impl() STATICLIB_NOEXCEPT { }

    Impl(const std::string& mustache_file_path, const ss::JsonValue& json,
            const std::map<std::string, std::string>& partials) try :
        renderer(utils::read_file_to_string(mustache_file_path), utils::create_mstch_node(json), partials) {
    } catch (const std::exception& e) {
        throw MustacheException(TRACEMSG(e.what() +
                "\nError processing mustache template: [" + mustache_file_path + "]" +
                " with values: [" + ss::dump_json_to_string(json) + "]"));
    }

    std::streamsize read(MustacheSource&, char* buffer, std::streamsize length) {
        return renderer.read(buffer, length);
    }   

};
PIMPL_FORWARD_CONSTRUCTOR(MustacheSource, (const std::string&)
        (const staticlib::serialization::JsonValue&)(partmap_type), (), MustacheException)
PIMPL_FORWARD_METHOD(MustacheSource, std::streamsize, read, (char*) (std::streamsize), (), MustacheException)
    
} // namespace
}
