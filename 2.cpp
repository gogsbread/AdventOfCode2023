#include "common.h"

namespace {
int p1(const std::vector<std::string> &in) {
  int r{0};
  for (const auto &l : in) {
    bool fail{false};
    const auto gid = gb::split(l, ": ").at(0);
    const auto g = gb::split(l, ": ").at(1);
    for (const auto &s : gb::split(g, "; ")) {
      for (const auto &c : gb::split(s, ", ")) {
        int n;
        std::string col;
        gb::sscanf(c, "%d %[^,;]", n, col);
        if (col == "blue" && n > 14)
          fail = fail || true;
        if (col == "red" && n > 12)
          fail = fail || true;
        if (col == "green" && n > 13)
          fail = fail || true;
      }
    }
    if (!fail) {
      int n;
      gb::sscanf(gid, "Game %d", n);
      r += n;
    }
  }
  return r;
}

int64_t p2(const std::vector<std::string> &in) {
  int64_t t{0};
  for (const auto &l : in) {
    int r{1}, b{1}, g{1};
    const auto gm = gb::split(l, ": ").at(1);
    for (const auto &s : gb::split(gm, "; ")) {
      for (const auto &c : gb::split(s, ", ")) {
        int n;
        std::string col;
        gb::sscanf(c, "%d %[^,;]", n, col);
        if (col == "blue")
          b = std::max(n, b);
        if (col == "red")
          r = std::max(n, r);
        if (col == "green")
          g = std::max(n, g);
      }
    }
    t += static_cast<int64_t>(r * b * g);
  }
  return t;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}