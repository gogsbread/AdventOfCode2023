#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <charconv>
#include <climits>
#include <cmath>
#include <complex>
#include <concepts>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

using vs = std::vector<std::string>;
#define ASSERT_EXPR(expr, err)                                                 \
  if (!(expr))                                                                 \
    throw std::runtime_error((err));

using namespace std::string_view_literals;
using namespace std::string_literals;

namespace gb {
std::vector<std::string_view> split(std::string_view sentence,
                                    std::string_view delim) {
  if (sentence.length() == 0)
    return {};
  if (delim.length() == 0)
    return {sentence};

  std::vector<std::string_view> r;
  std::string_view::size_type s{0}, e{0};
  while ((e = sentence.find(delim, s)) != sentence.npos) {
    r.emplace_back(sentence.substr(s, e - s));
    s = e + delim.length();
  }
  r.emplace_back(sentence.substr(s, sentence.length() - s));
  return r;
}

template <std::ranges::range T>
std::string join(const T &iterable, std::string delim) {
  auto begin = std::begin(iterable);
  auto end = std::end(iterable);
  if (begin == end)
    return std::string{};

  std::ostringstream oss{};
  oss << *begin++;
  while (begin != end) {
    oss << delim << *begin++;
  }
  return oss.str();
}

template <typename T> auto arg_handle(T &arg) {
  if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {
    arg.resize(100);
    return arg.data();
  } else {
    return &arg;
  }
}

template <typename T> auto arg_resize(T &arg) {
  if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {
    arg.resize(strlen(arg.data()));
  }
}

template <typename... Args>
void sscanf(const std::string_view in, const std::string_view fmt,
            Args &...args) {
  ::sscanf(in.data(), fmt.data(), arg_handle(args)...);
  (arg_resize(args), ...);
}

template <typename T> T svtoT(const std::string_view sv) {
  T v{};
  auto [_, ec] = std::from_chars(sv.data(), sv.data() + sv.length(), v);
  if (ec == std::errc::invalid_argument) {
    std::ostringstream ss{};
    ss << "Not a number " << std::quoted(sv);
    throw std::invalid_argument(ss.str());
  } else if (ec == std::errc::result_out_of_range) {
    std::ostringstream ss{};
    ss << "Out of range for " << typeid(T).name();
    throw std::invalid_argument(ss.str());
  }
  return v;
}

std::vector<std::string> readIn() {
  std::vector<std::string> lines;
  for (std::string l; getline(std::cin, l);) {
    lines.emplace_back(l);
  }
  return lines;
}

template <typename T> void writeOut(T s) { std::cout << s << std::endl; }
} // namespace gb