/* 
 * File:   mstch_utils.cpp
 * Author: alex
 * 
 * Created on October 28, 2016, 8:52 PM
 */

#include "mstch_utils.hpp"

#include "staticlib/config.hpp"
#include "staticlib/io.hpp"
#include "staticlib/utils.hpp"

namespace staticlib {
namespace mustache {
namespace utils {

namespace { // anonymous

namespace sc = staticlib::config;
namespace si = staticlib::io;
namespace ss = staticlib::serialization;
namespace su = staticlib::utils;

mstch::node create_map(const ss::JsonValue& value) {
    std::map<const std::string, mstch::node> map;
    for (const auto& fi : value.as_object()) {
        map.insert({fi.name(), create_mstch_node(fi.value())});
    }
    return mstch::node(std::move(map));
}

mstch::node create_array(const ss::JsonValue& value) {
    std::vector<mstch::node> array;
    for (const auto& va : value.as_array()) {
        array.emplace_back(create_mstch_node(va));
    }
    return mstch::node(std::move(array));
}

} // namespace

mstch::node create_mstch_node(const ss::JsonValue& value) {
    switch (value.type()) {
    case (ss::JsonType::NULL_T): return mstch::node();
    case (ss::JsonType::OBJECT): return create_map(value);
    case (ss::JsonType::ARRAY): return create_array(value);
    case (ss::JsonType::STRING): return mstch::node(value.as_string());
    case (ss::JsonType::INTEGER): return mstch::node(static_cast<int> (value.as_int64()));
    case (ss::JsonType::REAL): return mstch::node(value.as_double());
    case (ss::JsonType::BOOLEAN): return mstch::node(value.as_bool());
    default: throw MustacheException(TRACEMSG(
                "Unsupported JSON type:[" + sc::to_string(static_cast<char> (value.type())) + "]"));
    }
}

std::string read_file_to_string(const std::string& path) {
    su::FileDescriptor fd{path, 'r'};
    std::array<char, 4096> buf;
    si::string_sink sink{};
    si::copy_all(fd, sink, buf.data(), buf.size());
    return std::move(sink.get_string());
}    

} // namespace
}
}
