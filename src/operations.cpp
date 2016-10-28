/* 
 * File:   operations.cpp
 * Author: alex
 * 
 * Created on October 28, 2016, 8:39 PM
 */

#include "staticlib/mustache/operations.hpp"

#include "staticlib/tinydir.hpp"
#include "staticlib/utils.hpp"

#include "mstch_utils.hpp"

namespace staticlib {
namespace mustache {

namespace { // anonymous

namespace ss = staticlib::serialization;
namespace st = staticlib::tinydir;
namespace su = staticlib::utils;

} // namespace

std::map<std::string, std::string> load_partials(const std::string dirpath,
        const std::string& postfix) {
    std::map<std::string, std::string> res;
    for (const st::TinydirFile& tf : st::list_directory(dirpath)) {
        if (!(tf.is_regular_file() && su::ends_with(tf.get_name(), postfix))) continue;
        std::string name = std::string(tf.get_name().data(), tf.get_name().length() - postfix.length());
        std::string val = utils::read_file_to_string(tf.get_path());
        auto pa = res.insert(std::make_pair(std::move(name), std::move(val)));
        if (!pa.second) throw MustacheException(TRACEMSG(
                "Invalid duplicate partials element," +
                " dirpath: [" + dirpath + "], path: [" + tf.get_path() + "]"));
    }
    return res;
}

std::string render_string(const std::string& template_text, const ss::JsonValue& json,
        const std::map<std::string, std::string>& partials) {
    mstch::node node = utils::create_mstch_node(json);
    return mstch::render(template_text, node, partials);
}

} // namespace
}
