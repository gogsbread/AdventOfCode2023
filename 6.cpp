#include "common.h"

namespace {
int64_t p1(const std::vector<std::string> &in) {
  std::vector<int> times{};
  std::vector<int> distances{};
  {
    std::stringstream ss{in[0]};
    ss.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    std::copy(std::istream_iterator<int>(ss), std::istream_iterator<int>(),
              std::back_inserter(times));
  }
  {
    std::stringstream ss{in[1]};
    ss.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    std::copy(std::istream_iterator<int>(ss), std::istream_iterator<int>(),
              std::back_inserter(distances));
  }

  int64_t r{1};
  for (size_t i{0}; i < times.size(); ++i) {
    int t = times[i];
    int d = distances[i];
    // typical roots of quadratic eq: r(x - r) > y
    // -b +- sqrt(b^2 - 4ac) / 2a where a = -1, b = x, c = -y
    double l = (-t + sqrt(t * t - 4 * -1 * -d)) / -2.0;
    double u = (-t - sqrt(t * t - 4 * -1 * -d)) / -2.0;
    l = (ceil(l) == l)
            ? ceil(l) + 1
            : ceil(l); // if the roots are integers than > 0 cannot be
                       // satisified; so ignore the limits if they satisfy
    u = (floor(u) == u) ? floor(u) - 1 : floor(u);
    r *= (u - l + 1);
  }
  return r;
}

int64_t p2(const std::vector<std::string> &in) {
  int64_t t, d;
  {
    std::istringstream iss{in[0]};
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    std::ostringstream oss{};
    for (std::string s; iss >> s;) {
      oss << s;
    }
    t = std::stoll(oss.str());
  }
  {
    std::istringstream iss{in[1]};
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    std::ostringstream oss{};
    for (std::string s; iss >> s;) {
      oss << s;
    }
    d = std::stoll(oss.str());
  };

  double l = (-t + sqrt(t * t - 4 * -1 * -d)) / -2.0;
  double u = (-t - sqrt(t * t - 4 * -1 * -d)) / -2.0;
  l = (ceil(l) == l) ? ceil(l) + 1 : ceil(l);
  u = (floor(u) == u) ? floor(u) - 1 : floor(u);
  return (u - l + 1);
}
} // namespace

int main() {
  const auto &in = gb::readIn();
  gb::writeOut(p1(in));
  gb::writeOut(p2(in));
}