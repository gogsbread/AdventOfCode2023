#include "common.h"

namespace {
struct Map {
  int64_t src;
  int64_t dst;
  int64_t range;
};

int64_t mapper(std::vector<Map> &map, int64_t src) {
  for (const auto &s : map) {
    if (src >= s.src && src < s.src + s.range) {
      return s.dst + (src - s.src);
    }
  }
  return src;
}

int64_t inv_mapper(std::vector<Map> &map, int64_t dst) {
  for (const auto &s : map) {
    if (dst >= s.dst && dst < s.dst + s.range) {
      return s.src + (dst - s.dst);
    }
  }
  return dst;
}

int64_t p1(const std::vector<std::string> &in) {
  std::string mode;
  std::vector<int64_t> seeds{};
  std::vector<Map> soil{};
  std::vector<Map> fert{};
  std::vector<Map> water{};
  std::vector<Map> light{};
  std::vector<Map> temp{};
  std::vector<Map> hum{};
  std::vector<Map> loc{};
  {
    auto sds = gb::split(gb::split(in[0], ": "sv).at(1), " "sv);
    std::transform(
        sds.cbegin(), sds.cend(), std::back_inserter(seeds),
        [](const std::string_view s) { return std::stoll(std::string{s}); });
  }
  for (size_t i{2}; i < in.size(); ++i) {
    if (in[i].find("seed-to-soil") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        soil.emplace_back(m);
      }
    } else if (in[i].find("soil-to-fertilizer") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        fert.emplace_back(m);
      }
    } else if (in[i].find("fertilizer-to-water") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        water.emplace_back(m);
      }
    } else if (in[i].find("water-to-light") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        light.emplace_back(m);
      }
    } else if (in[i].find("light-to-temperature") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        temp.emplace_back(m);
      }
    } else if (in[i].find("temperature-to-humidity") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        hum.emplace_back(m);
      }
    } else if (in[i].find("humidity-to-location") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        loc.emplace_back(m);
      }
    }
  }

  int64_t r{std::numeric_limits<int64_t>::max()};
  for (int64_t v : seeds) {
    r = std::min(
        r,
        mapper(loc,
               mapper(hum,
                      mapper(temp,
                             mapper(light,
                                    mapper(water,
                                           mapper(fert, mapper(soil, v))))))));
  }
  return r;
}

int64_t p2(const std::vector<std::string> &in) {
  std::string mode;
  std::vector<Map> soil{};
  std::vector<Map> fert{};
  std::vector<Map> water{};
  std::vector<Map> light{};
  std::vector<Map> temp{};
  std::vector<Map> hum{};
  std::vector<Map> loc{};

  std::vector<int64_t> seeds{};
  {
    auto sds = gb::split(gb::split(in[0], ": "sv).at(1), " "sv);
    std::transform(
        sds.cbegin(), sds.cend(), std::back_inserter(seeds),
        [](const std::string_view s) { return std::stoll(std::string{s}); });
  }
  for (size_t i{2}; i < in.size(); ++i) {
    if (in[i].find("seed-to-soil") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        soil.emplace_back(m);
      }
    } else if (in[i].find("soil-to-fertilizer") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        fert.emplace_back(m);
      }
    } else if (in[i].find("fertilizer-to-water") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        water.emplace_back(m);
      }
    } else if (in[i].find("water-to-light") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        light.emplace_back(m);
      }
    } else if (in[i].find("light-to-temperature") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        temp.emplace_back(m);
      }
    } else if (in[i].find("temperature-to-humidity") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        hum.emplace_back(m);
      }
    } else if (in[i].find("humidity-to-location") != in[i].npos) {
      while (!in[++i].empty()) {
        Map m;
        gb::sscanf(in[i], "%lld %lld %lld", m.dst, m.src, m.range);
        loc.emplace_back(m);
      }
    }
  }

  int64_t u{std::numeric_limits<int64_t>::max()};
  {
    for (size_t i{0}; i < seeds.size(); i += 2) {
      u = std::min(
          u,
          mapper(loc,
                 mapper(hum,
                        mapper(temp,
                               mapper(light,
                                      mapper(water,
                                             mapper(fert,
                                                    mapper(soil,
                                                           seeds.at(i)))))))));
    }
  }

  for (int64_t l{0}; l <= u; ++l) {
    int64_t seed = inv_mapper(
        soil,
        inv_mapper(
            fert,
            inv_mapper(
                water,
                inv_mapper(
                    light,
                    inv_mapper(temp, inv_mapper(hum, inv_mapper(loc, l)))))));
    for (uint64_t i{0}; i < seeds.size(); i += 2) {
      if (seed >= seeds.at(i) && seed < seeds.at(i) + seeds.at(i + 1))
        return l;
    }
  }
  assert(false);
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}