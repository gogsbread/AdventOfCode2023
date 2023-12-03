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

long p2(const std::vector<std::string> &in) { return 0; }
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}