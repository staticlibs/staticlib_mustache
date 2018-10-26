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
 * File:   source.hpp
 * Author: alex
 *
 * Created on October 28, 2016, 8:39 PM
 */

#ifndef STATICLIB_MUSTACHE_SOURCE_HPP
#define STATICLIB_MUSTACHE_SOURCE_HPP

#include <map>
#include <string>

#include "staticlib/pimpl.hpp"
#include "staticlib/json.hpp"

#include "staticlib/mustache/mustache_exception.hpp"

namespace staticlib {
namespace mustache {

/**
 * 'Source' implementation that will render mustache output in streaming mode
 * (input file is loaded into memory though).
 */
class source : public sl::pimpl::object {
protected:
    /**
     * implementation class
     */
    class impl;

public:
    /**
     * PIMPL-specific constructor
     * 
     * @param pimpl impl object
     */
    PIMPL_CONSTRUCTOR(source)

    /**
     * Constructor
     * 
     * @param mustache_file_path path to template file
     * @param json values for template
     * @param partials partials map
     */
    source(const std::string& mustache_file_path, const sl::json::value& json,
            const std::map<std::string, std::string>& partials = std::map<std::string, std::string>());

    /**
     * Constructor
     * 
     * @param json values for template
     * @param mustache_file_contents contents of the mustache file
     * @param partials partials map
     */
    source(const sl::json::value& json, const std::string& mustache_file_contents,
            const std::map<std::string, std::string>& partials = std::map<std::string, std::string>());

    /**
     * Read method for 'Source'
     * 
     * @param span destination span
     * @return number of bytes written into buffer
     */
    std::streamsize read(sl::io::span<char> span);

};

} //namespace
}

#endif /* STATICLIB_MUSTACHE_SOURCE_HPP */

