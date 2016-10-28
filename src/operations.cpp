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
