#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;
using Pos = pair<ll, ll>;
using vP = vector<Pos>;
using Dict = map<ll, vP>;

ll n;
vvl B;
Dict D;

vl dx{-1, 1, 0, 0};
vl dy{0, 0, -1, 1};

void bfs(ll l, ll y, ll x) {
  queue<Pos> Q{};
  Q.push({y, x});
  B[y][x] = 0;

  while (!Q.empty()) {
    auto [fy, fx] = Q.front();
    Q.pop();

    D[l].push_back({fy, fx});

    for (auto d = 0; d < 4; ++d) {
      const auto& nx = fx + dx[d];
      const auto& ny = fy + dy[d];

      if (nx < 0 || n <= nx || ny < 0 || n <= ny) continue;
      if (B[ny][nx] == 0) continue;

      Q.push({ny, nx});
      B[ny][nx] = 0;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> n;
  B = vvl(n, vl(n));
  for (auto&& r : B) {
    for (auto&& b : r) {
      cin >> b;
    }
  }

  ll l = 1;
  for (auto i = 0; i < n; ++i) {
    for (auto j = 0; j < n; ++j) {
      if (B[i][j] == 0) continue;

      D[l] = vP{};
      bfs(l, i, j);
      ++l;
    }
  }

  ll ans = 100 * 100;
  for (auto i = 1; i < l; ++i) {
    const auto& v1 = D[i];
    for (auto j = i + 1; j <= l; ++j) {
      const auto& v2 = D[j];

      for (const auto& [y1, x1] : v1) {
        for (const auto& [y2, x2] : v2) {
          const auto& dist = abs(x1 - x2) + abs(y1 - y2) - 1;
          ans = min(ans, dist);
        }
      }
    }
  }

  cout << ans;

  return 0;
}