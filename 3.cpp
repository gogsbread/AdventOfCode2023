#include "common.h"

namespace {
int64_t p1(const std::vector<std::string> &in) {
  int64_t r{0};
  for (int j{0}; j < static_cast<int>(in.size()); ++j) {
    for (int i{0}; i < static_cast<int>(in[j].length()); ++i) {
      int num{0}, s{i}, e;
      while (i < static_cast<int>(in[j].length()) && isdigit(in[j][i])) {
        num = (num * 10) + (in[j][i] - '0');
        ++i;
      }
      e = i;
      if (e > s) {
        bool use{false};
        for (int m{std::max(j - 1, 0)};
             m < std::min(j + 2, static_cast<int>(in.size())); ++m) {
          for (int n{std::max(s - 1, 0)};
               n < std::min(e + 1, static_cast<int>(in[j].length())); ++n) {
            if (in[m][n] != '.' && !isdigit(in[m][n])) {
              use = true;
            }
          }
        }
        if (use)
          r += num;
      }
    }
  }
  return r;
}

int64_t p2(const std::vector<std::string> &in) {
  std::unordered_map<int, std::pair<int, int>> gears{};
  for (int j{0}; j < static_cast<int>(in.size()); ++j) {
    for (int i{0}; i < static_cast<int>(in[j].length()); ++i) {
      int num{0}, s{i}, e;
      while (i < static_cast<int>(in[j].length()) && isdigit(in[j][i])) {
        num = (num * 10) + (in[j][i] - '0');
        ++i;
      }
      e = i;
      if (e > s) {
        for (int m{std::max(j - 1, 0)};
             m < std::min(j + 2, static_cast<int>(in.size())); ++m) {
          for (int n{std::max(s - 1, 0)};
               n < std::min(e + 1, static_cast<int>(in[j].length())); ++n) {
            if (in[m][n] == '*') {
              int k = m * in[0].length() + n;
              if (gears.find(k) == gears.end()) {
                gears.emplace(k, std::make_pair(0, 1));
              }
              ++gears[k].first;
              gears[k].second *= num;
            }
          }
        }
      }
    }
  }
  int64_t r{0};
  for (const auto &[k, v] : gears) {
    if (v.first == 2)
      r += v.second;
  }
  return r;
}

} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}