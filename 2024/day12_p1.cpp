#include <bits/stdc++.h>

using pii = std::pair<int, int>;

std::array<pii, 4> dir {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

pii& operator+=(pii &l, const pii &r) {
    l.first += r.first;
    l.second += r.second;
    return l;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line); )
        a.push_back(line);

    int n = a.size(), m = a[0].size();
    std::println(stderr, "read {} x {} grid", n, m);

    std::vector<int> vis(n * m);
    auto dfs = [&](this auto dfs, int x, int y, int k) -> pii {
        vis[x * m + y] = k;
        pii res{1, 0};
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!(0 <= nx and nx < n and 0 <= ny and ny < m and a[nx][ny] == a[x][y]))
                continue;
            if (!vis[nx * m + ny])
                res += dfs(nx, ny, k);
            if (vis[nx * m + ny] == k)
                res.second++;
        }
        return res;
    };

    long long ans = 0;
    for (int i = 0, k = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vis[i * m + j]) continue;
            auto [area, common] = dfs(i, j, ++k);
            ans += area * (4LL * area - common);
        }
    }

    std::println("{}", ans);
}
