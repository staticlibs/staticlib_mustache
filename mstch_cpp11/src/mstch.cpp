#include <vector>
#include <cstdint>
#include <cstring>
#include <array>

#include "mstch/mstch.hpp"
#include "render_context.hpp"
#include "template_type.hpp"
#include "token.hpp"

using namespace mstch;

std::function<std::string(const std::string&)> mstch::config::escape;

std::string mstch::render(
    const std::string& tmplt,
    const node& root,
    const std::map<std::string,std::string>& partials)
{
  std::map<std::string, template_type> partial_templates;
  for (auto& partial: partials)
    partial_templates.insert({partial.first, {partial.second}});

  return render_context(root, partial_templates).render(tmplt);
     // streaming impl can be used here instead
//    auto ren = renderer(tmplt, root, partials);
//    std::array<char, 4096> buf;
//    std::string res;
//    std::streamsize read;
//    while (-1 != (read = ren.read(buf.data(), buf.size()))) {
//        res.append(buf.data(), read);
//    }
//    return res;
}

namespace mstch {
    
class renderer::impl {
  template_type tmplt;
  node root;
  std::vector<token>::const_iterator it;
  render_context ctx;
  std::string cur;
  size_t idx = 0;
  bool prev_eol = true;
  
public:    
  impl(const impl&) = delete;
  impl& operator=(const impl&) = delete;
    
  impl(
      const std::string& tmplt,
      node&& root,
      const std::map<std::string, std::string>& partials) :
    tmplt(tmplt), root(std::move(root)), it(this->tmplt.begin()) {
    std::map<std::string, template_type> partial_templates;
    for (auto& partial : partials) {
      partial_templates.insert({partial.first, {partial.second}});
    }
    this->ctx = render_context(this->root, partial_templates);
  }
  
  std::streamsize read(char* buffer, std::streamsize length) {
    if (idx < cur.length()) {
        return read_cur(buffer, length);
    }
    while (it != tmplt.end()) {
      const token& token = *it;
      it++;
      cur = ctx.render_token(token, prev_eol);
      idx = 0;
      prev_eol = token.eol();
      if (cur.length() > 0) {
        return read_cur(buffer, length);
      }
    }
    return std::char_traits<char>::eof();
  }
  
private:
  std::streamsize read_cur(char* buffer, std::streamsize length) {
    size_t avail = cur.length() - idx;
    size_t ulength = static_cast<size_t> (length);
    size_t len = avail <= ulength ? avail : ulength;
    std::memcpy(buffer, cur.data() + idx, len);
    idx += len;
    return static_cast<std::streamsize> (len);
  }
    
};

renderer::~renderer() = default;

renderer::renderer(renderer&& other) : pimpl(std::move(other.pimpl)) { }

renderer& renderer::operator=(renderer&& other) {
  this->pimpl = std::move(other.pimpl);
  return *this;
}

renderer::renderer(
    std::string tmplt,
    node root,
    const std::map<std::string, std::string>& partials) : 
  pimpl(new renderer::impl{tmplt, std::move(root), partials}){ }

std::streamsize renderer::read(char* buffer, std::streamsize length) {
  return pimpl->read(buffer, length);
}

}
