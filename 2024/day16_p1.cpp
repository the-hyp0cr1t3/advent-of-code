#include <bits/stdc++.h>

using i64 = long long;

struct state {
    int x, y, d;
    i64 dist;
    state(int x_, int y_, int d_, i64 dist_): x(x_), y(y_), d(d_), dist(dist_) {}
    bool operator<(const state& o) const { 
        return dist > o.dist; 
    }
}; 

constexpr i64 inf = 1e18;

std::array<int, 4> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

auto chmin = [](auto &A, auto B) { return B < A? A = B, true : false; };

int main() {
        std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line) and !line.empty(); )
        a.push_back(line);

    int n = a.size(), m = a[0].size(), sx, sy, ex, ey;
    std::println(stderr, "read {} x {} grid", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'S') sx = i, sy = j;
            if (a[i][j] == 'E') ex = i, ey = j;
        }
    }

    auto f = [&](int x, int y, int d) {
        return 4 * (m * x + y) + d;
    };

    auto dijkstra = [&](int rx, int ry) {
        std::vector<i64> dist(n * m * 4, inf);
        std::priority_queue<state> pq;
        pq.emplace(rx, ry, 1, dist[f(rx, ry, 1)] = 0);

        auto valid = [&](int x, int y) {
            return 0 <= x and x < n and 0 <= y and y < m and a[x][y] != '#';
        };

        while (!pq.empty()) {
            state t = pq.top();
            pq.pop();
            if (t.dist > dist[f(t.x, t.y, t.d)]) continue;

            int x = t.x + dx[t.d], y = t.y + dy[t.d];
            if (valid(x, y) and chmin(dist[f(x, y, t.d)], t.dist + 1))
                pq.emplace(x, y, t.d, t.dist + 1);

            if (chmin(dist[f(t.x, t.y, (t.d + 1) % 4)], t.dist + 1000))
                pq.emplace(t.x, t.y, (t.d + 1) % 4, t.dist + 1000);

            if (chmin(dist[f(t.x, t.y, (t.d + 3) % 4)], t.dist + 1000))
                pq.emplace(t.x, t.y, (t.d + 3) % 4, t.dist + 1000);
        }

        return dist;
    };

    auto sd = dijkstra(sx, sy);

    i64 ans = inf;
    for (int d = 0; d < 4; d++)
        ans = std::min(ans, sd[f(ex, ey, d)]);

    std::println("{}", ans);
}
