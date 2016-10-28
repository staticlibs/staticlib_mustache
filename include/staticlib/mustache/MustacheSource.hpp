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

    MustacheSource(const std::string& mustache_file_path, const staticlib::serialization::JsonValue& json,
            const std::map<std::string, std::string>& partials = std::map<std::string, std::string>());

    std::streamsize read(char* buffer, std::streamsize length);
            
};

} //namespace
}

#endif	/* STATICLIB_MUSTACHE_MUSTACHESOURCE_HPP */

