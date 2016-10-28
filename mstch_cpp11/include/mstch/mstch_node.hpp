#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <functional>

namespace mstch {

namespace internal {

template<class N>
class object_t {
 public:
  const N& at(const std::string& name) const {
    cache[name] = (methods.at(name))();
    return cache[name];
  }

  bool has(const std::string name) const {
    return methods.count(name) != 0;
  }

 protected:
  template<class S>
  void register_methods(S* s, std::map<std::string,N(S::*)()> methods) {
    for(auto& item: methods)
      this->methods.insert({item.first, std::bind(item.second, s)});
  }

 private:
  std::map<std::string, std::function<N()>> methods;
  mutable std::map<std::string, N> cache;
};

template<class T, class N>
class is_fun {
 private:
  using not_fun = char;
  using fun_without_args = char[2];
  using fun_with_args = char[3];
  template <typename U, U> struct really_has;
  template <typename C> static fun_without_args& test(
      really_has<N(C::*)() const, &C::operator()>*);
  template <typename C> static fun_with_args& test(
      really_has<N(C::*)(const std::string&) const,
      &C::operator()>*);
  template <typename> static not_fun& test(...);

 public:
  static bool const no_args = sizeof(test<T>(0)) == sizeof(fun_without_args);
  static bool const has_args = sizeof(test<T>(0)) == sizeof(fun_with_args);
};

template<class N>
using node_renderer = std::function<std::string(const N& n)>;

template<class N>
class lambda_t {
 public:
  lambda_t() { }
     
  template<class F>
  lambda_t(F f, typename std::enable_if<is_fun<F, N>::no_args>::type* = 0):
      fun([f](node_renderer<N> renderer, const std::string&) {
        return renderer(f());
      })
  {
  }

  template<class F>
  lambda_t(F f, typename std::enable_if<is_fun<F, N>::has_args>::type* = 0):
      fun([f](node_renderer<N> renderer, const std::string& text) {
        return renderer(f(text));
      })
  {
  }

  std::string operator()(node_renderer<N> renderer,
      const std::string& text = "") const
  {
    return fun(renderer, text);
  }

 private:
  std::function<std::string(node_renderer<N> renderer, const std::string&)> fun;
};

}

// original variant

//using node = boost::make_recursive_variant<
//    std::nullptr_t, 
//    std::string, 
//    int, 
//    double, 
//    bool,
//    internal::lambda_t<boost::recursive_variant_>,
//    std::shared_ptr<internal::object_t<boost::recursive_variant_>>,
//    std::map<const std::string, boost::recursive_variant_>,
//    std::vector<boost::recursive_variant_>
//    >::type;

enum class node_type {
    NULL_T,
    STRING,
    INT,
    DOUBLE,
    BOOL,
    LAMBDA,
    OBJECT,
    MAP,
    ARRAY
};

// mstch requires 'node' to be copyable - using shared_ptrs for safety
// tagged union is possible here, but tricky as 
// unfortunately VS2013 doesn't support unrestricted unions
// see example: https://github.com/staticlibs/staticlib_serialization/blob/770a4c751558837af19ad852f8b32c0e97de1ebb/include/staticlib/serialization/JsonValue.hpp#L76
// storing map and array together to avoid additional shared_ptr

class node {
private:    
    using map_or_array_type = std::pair<std::map<const std::string, node>, std::vector<node>>;
    
    node_type type;

    std::nullptr_t null_value;
    std::string string_value;
    int int_value;
    double double_value;
    bool bool_value;
    internal::lambda_t<node> lambda_value;
    std::shared_ptr<internal::object_t<node>> object_value;        
    std::shared_ptr<map_or_array_type> map_or_array_value;
         
public:
    node() :
    type(node_type::NULL_T) { }    
    
    // don't know whether to create map or array, from initializer_list
    // let's create neither
    node(const std::initializer_list<node>&) :
    type(node_type::NULL_T) { }
    
    node(std::nullptr_t) :
    type(node_type::NULL_T) { }

    node(std::string string_value) :
    type(node_type::STRING), string_value(std::move(string_value)) { }

    node(int int_value) :
    type(node_type::INT), int_value(int_value) { }

    node(double double_value) :
    type(node_type::DOUBLE), double_value(double_value) { }

    node(bool bool_value) :
    type(node_type::BOOL), bool_value(bool_value) { }

    node(const internal::lambda_t<node>& lambda_value) :
    type(node_type::LAMBDA), lambda_value(lambda_value) { }

    template <typename T>
    node(std::shared_ptr<T> object_value) :
    type(node_type::OBJECT), object_value(std::move(object_value)) { }

    node(const std::map<const std::string, node>& map_value) :
    type(node_type::MAP), map_or_array_value(std::make_shared<map_or_array_type>()) {
        std::map<const std::string, node> tmp = map_value;
        this->map_or_array_value->first = std::move(tmp);
    }

    node(std::map<const std::string, node>&& map_value) :
    type(node_type::MAP), map_or_array_value(std::make_shared<map_or_array_type>()) {
        this->map_or_array_value->first = std::move(map_value);
    }    

    node(const std::vector<node>& array) :
    type(node_type::ARRAY), map_or_array_value(std::make_shared<map_or_array_type>()) {
        std::vector<node> tmp = array;
        this->map_or_array_value->second = std::move(tmp);
    }

    node(std::vector<node>&& array) :
    type(node_type::ARRAY), map_or_array_value(std::make_shared<map_or_array_type>()) {
        this->map_or_array_value->second = std::move(array);
    }
    
    template<typename Visitor>
    typename Visitor::result_type apply_visitor(const Visitor& visitor) const {
        switch (type) {
            case node_type::NULL_T: 
                return visitor(null_value);
            case node_type::STRING: 
                return visitor(string_value);
            case node_type::INT:
                return visitor(int_value);
            case node_type::DOUBLE: 
                return visitor(double_value);
            case node_type::BOOL:
                return visitor(bool_value);
            case node_type::LAMBDA:
                return visitor(lambda_value);
            case node_type::OBJECT: 
                return visitor(object_value);
            case node_type::MAP: 
                return visitor(map_or_array_value->first);
            case node_type::ARRAY:
                return visitor(map_or_array_value->second);
            default: 
                return visitor(null_value);
        }
    }

    std::string& get_string() {
        if (node_type::STRING == this->type) {
            return string_value;
        } else {
            return empty_string();
        }
    }

    int get_int() {
        if (node_type::INT == this->type) {
            return int_value;
        } else {
            return 0;
        }
    }

    double get_double() {
        if (node_type::DOUBLE == this->type) {
            return double_value;
        } else {
            return 0;
        }
    }

    double get_bool() {
        if (node_type::BOOL == this->type) {
            return bool_value;
        } else {
            return false;
        }
    }    
    
    internal::lambda_t<node>& get_lambda() {
        if (node_type::LAMBDA == this->type) {
            return lambda_value;
        } else {
            return empty_lambda();
        }
    }
    
    std::shared_ptr<internal::object_t<node>>& get_object() {
        if (node_type::OBJECT == this->type) {
            return object_value;
        } else {
            return empty_object();
        }
    }
    
    std::map<const std::string, node>& get_map() {
        if (node_type::MAP == this->type) {
            return map_or_array_value->first;
        } else {
            return empty_map();
        }
    }

    std::vector<node>& get_array() {
        if (node_type::ARRAY == this->type) {
            return map_or_array_value->second;
        } else {
            return empty_array();
        }
    }
    
private:
    std::string& empty_string() {
        static std::string empty{""};
        return empty;
    }
    
    internal::lambda_t<node>& empty_lambda() {
        static internal::lambda_t<node> empty{};
        return empty;
    }

    std::shared_ptr<internal::object_t<node>>& empty_object() {
        static std::shared_ptr<internal::object_t<node>> empty{};
        return empty;
    }
    
    std::map<const std::string, node>& empty_map() {
        static std::map<const std::string, node> empty{};
        return empty;
    }
    
    std::vector<node>& empty_array() {
        static std::vector<node> empty{0};
        return empty;
    }
    
};

}
