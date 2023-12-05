#include "common.h"

namespace {
int p1(const std::vector<std::string> &in) {
  int t{0};
  for (const auto &l : in) {
    const auto c = gb::split(l, ": ").at(1);
    const auto w = gb::split(c, " | ").at(0);
    const auto h = gb::split(c, " | ").at(1);
    std::vector<int> win{};
    {
      std::istringstream ss{std::string{w}};
      int v;
      while (ss >> v) {
        win.emplace_back(v);
      }
    }
    std::vector<int> hand{};
    {
      std::istringstream ss{std::string{h}};
      int v;
      while (ss >> v) {
        hand.emplace_back(v);
      }
    }
    int cnt = std::count_if(hand.cbegin(), hand.cend(), [&win](const auto num) {
      return std::find(win.cbegin(), win.cend(), num) != win.end();
    });
    t += (cnt > 0) ? (1 << (cnt - 1)) : 0;
  }
  return t;
}

int p2(const std::vector<std::string> &in) {
  std::vector<int> cards(in.size() + 1, 1);
  for (const auto &l : in) {
    int crd;
    gb::sscanf(gb::split(l, ": ").at(0), "Card %d", crd);
    const auto c = gb::split(l, ": ").at(1);
    const auto w = gb::split(c, " | ").at(0);
    const auto h = gb::split(c, " | ").at(1);
    std::vector<int> win{};
    {
      std::istringstream ss{std::string{w}};
      int v;
      while (ss >> v) {
        win.emplace_back(v);
      }
    }
    std::vector<int> hand{};
    {
      std::istringstream ss{std::string{h}};
      int v;
      while (ss >> v) {
        hand.emplace_back(v);
      }
    }
    int cnt = std::count_if(hand.cbegin(), hand.cend(), [&win](const auto num) {
      return std::find(win.cbegin(), win.cend(), num) != win.end();
    });
    for (int i{crd + 1}; i <= crd + cnt; ++i) {
      cards.at(i) += cards.at(crd);
    }
  }
  return std::accumulate(cards.cbegin() + 1, cards.cend(), 0);
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}