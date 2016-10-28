/* 
 * File:   MustacheException.hpp
 * Author: alex
 *
 * Created on October 28, 2016, 8:40 PM
 */

#ifndef STATICLIB_MUSTACHE_MUSTACHEEXCEPTION_HPP
#define	STATICLIB_MUSTACHE_MUSTACHEEXCEPTION_HPP

#include "staticlib/config/BaseException.hpp"

namespace staticlib {
namespace mustache {

/**
 * Module specific exception
 */
class MustacheException : public staticlib::config::BaseException {
public:
    /**
     * Default constructor
     */
    MustacheException() = default;

    /**
     * Constructor with message
     * 
     * @param msg error message
     */
    MustacheException(const std::string& msg) :
    staticlib::config::BaseException(msg) { }

};

} //namespace
}

#endif	/* STATICLIB_MUSTACHE_MUSTACHEEXCEPTION_HPP */

