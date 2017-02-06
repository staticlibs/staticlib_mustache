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
 * File:   MustacheSource.hpp
 * Author: alex
 *
 * Created on October 28, 2016, 8:39 PM
 */

#ifndef STATICLIB_MUSTACHE_MUSTACHESOURCE_HPP
#define	STATICLIB_MUSTACHE_MUSTACHESOURCE_HPP

#include <map>
#include <string>

#include "staticlib/pimpl.hpp"
#include "staticlib/serialization/JsonValue.hpp"

#include "staticlib/mustache/MustacheException.hpp"

namespace staticlib {
namespace mustache {

/**
 * 'Source' implementation that will render mustache output in streaming mode
 * (input file is loaded into memory though).
 */
class MustacheSource : public staticlib::pimpl::PimplObject {
protected:
    /**
     * Implementation class
     */
    class Impl;

public:
    /**
     * PIMPL-specific constructor
     * 
     * @param pimpl impl object
     */
    PIMPL_CONSTRUCTOR(MustacheSource)

    /**
     * Constructor
     * 
     * @param mustache_file_path path to template file
     * @param json values for template
     * @param partials partials map
     */
    MustacheSource(const std::string& mustache_file_path, const staticlib::serialization::JsonValue& json,
            const std::map<std::string, std::string>& partials = std::map<std::string, std::string>());

    /**
     * Read method for 'Source'
     * 
     * @param span destination span
     * @return number of bytes written into buffer
     */
    std::streamsize read(staticlib::config::span<char> span);
            
};

} //namespace
}

#endif	/* STATICLIB_MUSTACHE_MUSTACHESOURCE_HPP */

