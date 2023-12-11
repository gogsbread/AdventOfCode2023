#include "common.h"

namespace {
enum class Type { HC, ONP, TWP, THK, FH, FRK, FVK };

std::unordered_map<char, int> count(std::string_view sv) {
  std::unordered_map<char, int> cnt{};
  for (char c : sv) {
    ++cnt[c];
  }
  return cnt;
}

struct Hand {
  std::string_view cards;
  int bid;
};

int64_t p1(const std::vector<std::string> &in) {
  std::vector<Hand> hands{};
  for (const auto &l : in) {
    const auto sp = gb::split(l, " ");
    hands.emplace_back(sp.at(0), gb::svtoT<int>(sp.at(1)));
  }

  const auto rank = [](char c) -> int {
    if (c == 'A')
      return 14;
    if (c == 'K')
      return 13;
    if (c == 'Q')
      return 12;
    if (c == 'J')
      return 11;
    if (c == 'T')
      return 10;
    if (c >= '2' && c <= '9')
      return c - '0';
    assert(false);
  };

  const auto type = [](std::string_view cards) -> Type {
    auto cnt = count(cards);
    if (cnt.size() == 1) {
      return Type::FVK;
    }
    if (cnt.size() == 2) {
      if (cnt.cbegin()->second == 1 || cnt.cbegin()->second == 4) {
        return Type::FRK;
      } else {
        return Type::FH;
      }
    }
    if (cnt.size() == 3) {
      for (const auto [k, v] : cnt) {
        if (v == 3)
          return Type::THK;
      }
      return Type::TWP;
    }
    if (cnt.size() == 5) {
      return Type::HC;
    }
    return Type::ONP;
  };

  const auto handsort = [rank, type](Hand a, Hand b) -> bool {
    auto cnta = count(a.cards);
    auto cntb = count(b.cards);
    if (type(a.cards) == type(b.cards)) {
      for (size_t i{0}; i < a.cards.length(); ++i) {
        if (a.cards[i] != b.cards[i]) {
          return rank(a.cards[i]) < rank(b.cards[i]);
        }
      }
      assert(false);
    }
    return type(a.cards) < type(b.cards);
  };

  std::sort(hands.begin(), hands.end(), handsort);
  int64_t r{0};
  {
    size_t i{hands.size()};
    for (auto it = hands.rbegin(); it != hands.rend(); ++it, --i) {
      r += (it->bid * i);
    }
  }
  return r;
}

int64_t p2(const std::vector<std::string> &in) {
  std::vector<Hand> hands{};
  for (const auto &l : in) {
    const auto sp = gb::split(l, " ");
    hands.emplace_back(sp.at(0), gb::svtoT<int>(sp.at(1)));
  }

  const auto rank = [](char c) -> int {
    if (c == 'A')
      return 14;
    if (c == 'K')
      return 13;
    if (c == 'Q')
      return 12;
    if (c == 'T')
      return 11;
    if (c >= '2' && c <= '9')
      return c - '0' + 1;
    if (c == 'J')
      return 2;
    assert(false);
  };

  const auto type = [](const std::string_view cards) -> Type {
    auto cnt = count(cards);
    if (cnt.size() == 1) {
      return Type::FVK;
    }

    // take the maximum element and bump it by how many ever J you have
    size_t j = cnt['J'];
    std::erase_if(cnt, [](const auto &item) { return item.first == 'J'; });
    const auto mx =
        *std::max_element(cnt.cbegin(), cnt.cend(),
                          [](std::pair<char, int> a, std::pair<char, int> b) {
                            return a.second < b.second;
                          });
    if (mx.second + j == 5) {
      return Type::FVK;
    }
    if (mx.second + j == 4) {
      return Type::FRK;
    }
    if (mx.second + j == 3) {
      if (cnt.size() == 2)
        return Type::FH;
      else
        return Type::THK;
    }
    if (mx.second + j == 2) {
      if (cnt.size() == 3)
        return Type::TWP;
      else
        return Type::ONP;
    }
    return Type::HC;
  };

  const auto handsort = [rank, type](Hand a, Hand b) -> bool {
    auto cnta = count(a.cards);
    auto cntb = count(b.cards);
    if (type(a.cards) == type(b.cards)) {
      for (size_t i{0}; i < a.cards.length(); ++i) {
        if (a.cards[i] != b.cards[i]) {
          return rank(a.cards[i]) < rank(b.cards[i]);
        }
      }
      assert(false);
    }
    return type(a.cards) < type(b.cards);
  };

  std::sort(hands.begin(), hands.end(), handsort);
  int64_t r{0};
  {
    size_t i{hands.size()};
    for (auto it = hands.rbegin(); it != hands.rend(); ++it, --i) {
      r += (it->bid * i);
    }
  }
  return r;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}