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

#include "staticlib/serialization/JsonValue.hpp"

#include "staticlib/mustache/MustacheException.hpp"

namespace staticlib {
namespace mustache {

std::map<std::string, std::string> load_partials(const std::string dirpath,
        const std::string& postfix = ".mustache");

std::string render_string(const std::string& template_text, 
        const staticlib::serialization::JsonValue& json,
        const std::map<std::string, std::string>& partials = std::map<std::string, std::string>());

} // namespace
}

#endif	/* STATICLIB_MUSTACHE_OPERATIONS_HPP */

