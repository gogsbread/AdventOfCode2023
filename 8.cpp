#include "common.h"

namespace {
int p1(const std::vector<std::string> &in) {
  std::vector<int8_t> ins{};
  {
    for (const char c : in[0]) {
      ins.emplace_back((c == 'L') ? 0 : 1);
    }
  }
  std::unordered_map<std::string, std::array<std::string, 2>> map{};
  for (size_t i{2}; i < in.size(); ++i) {
    std::string s, l, r;
    gb::sscanf(in[i], "%s = (%[^,], %[^)])", s, l, r);
    map[s] = std::array{l, r};
  }

  int r{0};
  {
    std::string k{"AAA"};
    while ((k = map[k][ins[r++ % ins.size()]]) != "ZZZ")
      ;
  }
  return r;
}

int64_t p2(const std::vector<std::string> &in) {
  std::vector<int8_t> ins{};
  {
    for (const char c : in[0]) {
      ins.emplace_back((c == 'L') ? 0 : 1);
    }
  }
  std::unordered_map<std::string, std::array<std::string, 2>> map{};
  for (size_t i{2}; i < in.size(); ++i) {
    std::string s, l, r;
    gb::sscanf(in[i], "%s = (%[^,], %[^)])", s, l, r);
    map[s] = std::array{l, r};
  }

  std::vector<std::string> aas{};
  for (const auto &[key, val] : map) {
    if (key.back() == 'A')
      aas.emplace_back(key);
  }
  std::vector<int64_t> zzs(aas.size());
  for (size_t i{0}, k{0}; i < aas.size(); ++i, k = 0) {
    while ((aas[i] = map[aas[i]][ins[k++ % ins.size()]]).back() != 'Z')
      ;
    zzs[i] = k;
  }
  int64_t r{zzs[0]};
  for (size_t i{1}; i < zzs.size(); ++i) {
    r = std::lcm(r, zzs[i]);
  }
  return r;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}