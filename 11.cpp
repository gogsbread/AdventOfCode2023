#include "common.h"

namespace {

template <int Fac> int64_t p(const std::vector<std::string> &in) {
  std::vector<std::pair<int, int>> galaxies{};
  for (size_t i{0}; i < in.size(); ++i) {
    for (size_t j{0}; j < in[i].size(); ++j) {
      if (in[i][j] == '#') {
        galaxies.emplace_back(i, j);
      }
    }
  }

  std::ranges::sort(galaxies, {}, &std::pair<int, int>::first);
  int64_t row_offset{0};
  for (size_t i{0}, j{0}; i < in.size() && j < galaxies.size();
       i = std::min(static_cast<int>(i + 1), galaxies[j].first)) {
    if (static_cast<int>(i) < galaxies[j].first) {
      row_offset += j * (galaxies.size() - j) * Fac;
    } else {
      ++j;
    }
  }
  std::ranges::sort(galaxies, {}, &std::pair<int, int>::second);
  int64_t col_offset{0};
  for (size_t i{0}, j{0}; i < in[0].size() && j < galaxies.size();
       i = std::min(static_cast<int>(i + 1), galaxies[j].second)) {
    if (static_cast<int>(i) < galaxies[j].second) {
      col_offset += j * (galaxies.size() - j) * Fac;
    } else {
      ++j;
    }
  }

  int64_t r{0};
  for (size_t i{0}; i < galaxies.size(); ++i) {
    for (size_t j{i + 1}; j < galaxies.size(); ++j) {
      r += std::abs(std::abs(galaxies[i].first - galaxies[j].first) +
                    std::abs(galaxies[i].second - galaxies[j].second));
    }
  }
  return r + row_offset + col_offset;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p<1>(in));
  gb::writeOut(p<9>(in));
  gb::writeOut(p<99>(in));
  gb::writeOut(p<999999>(in));
}