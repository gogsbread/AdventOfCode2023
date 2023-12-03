#include "common.h"

namespace {
int p1(const std::vector<std::string> &in) {
  int r{0};
  for (const auto &s : in) {
    auto st = s.find_first_of("0123456789");
    assert(st != s.npos);
    auto ed = s.find_last_of("0123456789");
    assert(ed != s.npos);
    r += std::stoi(""s + s[st] + s[ed]);
  }
  return r;
}

int p2(const std::vector<std::string> &in) {
  constexpr std::array<const char *, 9> v{
      "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  int r{0};
  for (const auto &l : in) {
    std::set<std::pair<size_t, std::string>> pos{};
    for (size_t i{0}; i < v.size(); ++i) {
      if (auto p = l.find(v[i]); p != l.npos) {
        pos.emplace(p, std::to_string(i + 1));
      }
      if (auto p = l.rfind(v[i]); p != l.npos) {
        pos.emplace(p, std::to_string(i + 1));
      }
    }
    if (auto d = l.find_first_of("0123456789"); d != l.npos) {
      pos.emplace(d, std::string{l[d]});
    }
    if (auto d = l.find_last_of("0123456789"); d != l.npos) {
      pos.emplace(d, std::string{l[d]});
    }
    assert(pos.size() > 0);
    r += std::stoi(pos.begin()->second + pos.rbegin()->second);
  }
  return r;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}