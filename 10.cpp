#include "common.h"

namespace {
struct P {
  int x;
  int y;
  P operator+(const P &p) const { return P{x + p.x, y + p.y}; }
  bool operator==(const P &p) const { return x == p.x && y == p.y; }
};

std::ostream &operator<<(std::ostream &os, const P &p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}

using Pipe = std::array<P, 2>;
using Row = std::vector<Pipe>;
using Grid = std::vector<Row>;

std::ostream &operator<<(std::ostream &os, const Pipe &p) {
  os << "(" << p[0].x << ", " << p[0].y << ")"
     << "(" << p[1].x << ", " << p[1].y << ")";
  return os;
}

auto parse(const std::vector<std::string> &in) {
  Grid g{};
  P s;
  for (size_t i{0}; i < in.size(); ++i) {
    Row r{};
    for (size_t j{0}; j < in[i].size(); ++j) {
      char c = in[i][j];
      if (c == '|') {
        r.emplace_back(Pipe{P{0, 1}, P{0, -1}});
      } else if (c == '-') {
        r.emplace_back(Pipe{P{1, 0}, P{-1, 0}});
      } else if (c == 'L') {
        r.emplace_back(Pipe{P{0, -1}, P{1, 0}});
      } else if (c == 'J') {
        r.emplace_back(Pipe{P{0, -1}, P{-1, 0}});
      } else if (c == '7') {
        r.emplace_back(Pipe{P{0, 1}, P{-1, 0}});
      } else if (c == 'F') {
        r.emplace_back(Pipe{P{0, 1}, P{1, 0}});
      } else if (c == '.') {
        r.emplace_back(Pipe{P{0, 0}, P{0, 0}});
      } else if (c == 'S') {
        r.emplace_back(Pipe{P{1, 1}, P{1, 1}}); // dummy
        s = P{static_cast<int>(j), static_cast<int>(i)};
      }
    }
    g.emplace_back(std::move(r));
  }
  return std::make_pair(g, s);
}

int p1(const std::vector<std::string> &in) {
  const auto [g, s] = parse(in);

  auto connects = [&g, s](const P &s_, const P &d_) {
    const Pipe &ps = g[s_.y][s_.x];
    const Pipe &pd = g[d_.y][d_.x];
    if ((s_ + ps.at(0) == d_ || s_ + ps.at(1) == d_ || s_ == s) &&
        (d_ + pd.at(0) == s_ || d_ + pd.at(1) == s_ || d_ == s)) {
      return true;
    }
    return false;
  };

  int step{0};
  std::vector<P> dirs{P{-1, 0}, P{1, 0}, P{0, -1}, P{0, 1}};
  std::pair<P, std::vector<P>> next{s, dirs};
  do {
    const P u = next.first;
    for (const P &d : next.second) {
      const P v = u + d;
      if (connects(u, v)) {
        std::vector<P> dir;
        std::copy_if(dirs.begin(), dirs.end(), std::back_inserter(dir),
                     [&d](const P a) {
                       return a != P{-d.x, -d.y};
                     });
        next = {v, dir};
        break;
      }
    }
    ++step;
  } while (next.first != s);
  return step / 2;
}

int p2(const std::vector<std::string> &in) {
  const auto [g, s] = parse(in);

  auto connects = [&g, s](const P &s_, const P &d_) {
    const Pipe &ps = g[s_.y][s_.x];
    const Pipe &pd = g[d_.y][d_.x];
    if ((s_ + ps.at(0) == d_ || s_ + ps.at(1) == d_ || s_ == s) &&
        (d_ + pd.at(0) == s_ || d_ + pd.at(1) == s_ || d_ == s)) {
      return true;
    }
    return false;
  };

  std::vector<P> tiles{s};
  std::vector<P> dirs{P{-1, 0}, P{1, 0}, P{0, -1}, P{0, 1}};
  std::pair<P, std::vector<P>> next{s, dirs};
  do {
    const P u = next.first;
    for (const P &d : next.second) {
      const P v = u + d;
      if (connects(u, v)) {
        std::vector<P> dir;
        std::copy_if(dirs.begin(), dirs.end(), std::back_inserter(dir),
                     [&d](const P a) {
                       return a != P{-d.x, -d.y};
                     });
        next = {v, dir};
        tiles.emplace_back(std::move(v));
        break;
      }
    }
  } while (next.first != s);

  // Brilliant Redditors suggested Shoelace(for area) & Pick's(for
  // non-pipe tiles). I was thinking about floodfill or even just counting from
  // left to right but wasn't sure how to get that right considering edge cases.
  // https://www.reddit.com/r/adventofcode/comments/18evyu9/comment/kcqmhwk/?utm_source=share&utm_medium=web2x&context=3
  int twice_area{0};
  for (size_t i{0}; i < tiles.size() - 1; ++i) {
    twice_area += tiles[i].x * tiles[i + 1].y;
  }
  for (size_t i{0}; i < tiles.size() - 1; ++i) {
    twice_area -= tiles[i].y * tiles[i + 1].x;
  }
  return (abs(twice_area) + 2 - (tiles.size() - 1)) / 2;
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}