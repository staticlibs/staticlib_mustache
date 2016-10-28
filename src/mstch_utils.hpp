/* 
 * File:   mstch_utils.hpp
 * Author: alex
 *
 * Created on October 28, 2016, 8:52 PM
 */

#ifndef STATICLIB_MUSTACHE_MSTCH_UTILS_HPP
#define	STATICLIB_MUSTACHE_MSTCH_UTILS_HPP

#include "mstch/mstch.hpp"

#include "staticlib/serialization.hpp"

#include "staticlib/mustache/MustacheException.hpp"

namespace staticlib {
namespace mustache {
namespace utils {

mstch::node create_mstch_node(const staticlib::serialization::JsonValue& value);

std::string read_file_to_string(const std::string& path);

} // namespace
}
}

#endif	/* STATICLIB_MUSTACHE_MSTCH_UTILS_HPP */

