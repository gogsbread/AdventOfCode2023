#include "common.h"

namespace {
int64_t p1(const std::vector<std::string> &in) {
  int64_t r{0};
  for (const auto &l : in) {
    std::vector<int64_t> v;
    std::ranges::transform(
        gb::split(l, " "), std::back_inserter(v),
        [](const auto sv) { return gb::svtoT<int64_t>(sv); });
    for (int i{static_cast<int>(v.size()) - 1}; i >= 0; --i) {
      for (int j{0}; j < i; ++j) {
        v[j] = v[j + 1] - v[j];
      }
    }
    r += std::accumulate(v.cbegin(), v.cend(), static_cast<int64_t>(0),
                         std::plus{});
  }
  return r;
}

int64_t p2(const std::vector<std::string> &in) {
  int64_t r{0};
  for (const auto &l : in) {
    std::vector<int64_t> v;
    std::ranges::transform(
        gb::split(l, " "), std::back_inserter(v),
        [](const auto sv) { return gb::svtoT<int64_t>(sv); });
    for (int i{0}; i < static_cast<int>(v.size()); ++i) {
      for (int j{static_cast<int>(v.size()) - 1}; j > i; --j) {
        v[j] = v[j] - v[j - 1];
      }
    }
    r += std::accumulate(v.crbegin(), v.crend(), static_cast<int64_t>(0),
                         [](const auto a, const auto b) { return b - a; });
  }
  return r;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}