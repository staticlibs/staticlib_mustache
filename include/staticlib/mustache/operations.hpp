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
 * File:   operations.hpp
 * Author: alex
 *
 * Created on October 28, 2016, 8:39 PM
 */

#ifndef STATICLIB_MUSTACHE_OPERATIONS_HPP
#define	STATICLIB_MUSTACHE_OPERATIONS_HPP

#include <map>
#include <string>

#include "staticlib/serialization/json_value.hpp"

#include "staticlib/mustache/mustache_exception.hpp"

namespace staticlib {
namespace mustache {

/**
 * Loads all files with specified postfix from specified directory into
 * 'filename (without postfix)' -> 'contents' map
 * 
 * @param dirpath path to directory that contain patrial files
 * @param postfix partial files postfix, ".mustache" by default
 * @return partials map
 */
std::map<std::string, std::string> load_partials(const std::string dirpath,
        const std::string& postfix = ".mustache");

/**
 * Renders mustache template with specified values
 * 
 * @param template_text template text
 * @param json json values for template
 * @param partials partials map
 * @return rendered string
 */
std::string render_string(const std::string& template_text, 
        const staticlib::serialization::json_value& json,
        const std::map<std::string, std::string>& partials = std::map<std::string, std::string>());

} // namespace
}

#endif	/* STATICLIB_MUSTACHE_OPERATIONS_HPP */

