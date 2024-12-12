#include <bits/stdc++.h>

std::array<std::pair<int, int>, 4> dir {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line); )
        a.push_back(line);

    int n = a.size(), m = a[0].size();
    std::println(stderr, "read {} x {} grid", n, m);

    auto f = [&](int x, int y) {
        return x * m + y;
    };

    auto valid = [&](int x, int y) {
        return 0 <= x and x < n and 0 <= y and y < m;
    };

    std::vector<int> vis(n * m, -1);
    auto dfs = [&](this auto dfs, int x, int y, int k) -> int {
        vis[f(x, y)] = k;
        int cnt = 1;
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!valid(nx, ny) or a[nx][ny] != a[x][y])
                continue;
            if (vis[f(nx, ny)] == -1)
                cnt += dfs(nx, ny, k);
        }
        return cnt;
    };

    std::vector<int> area;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (vis[f(i, j)] == -1)
                area.push_back(dfs(i, j, area.size()));
    
    std::vector<int> corners(area.size());
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            std::map<int, int> cnt;
            
            if (valid(i - 1, j - 1))
                ++cnt[vis[f(i - 1, j - 1)]];
            if (valid(i - 1, j))
                ++cnt[vis[f(i - 1, j)]];
            if (valid(i, j - 1))
                ++cnt[vis[f(i, j - 1)]];
            if (valid(i, j))
                ++cnt[vis[f(i, j)]];
            
            for (auto [k, c] : cnt)
                if (c & 1) corners[k]++;

            if (valid(i - 1, j - 1) and valid(i, j)) {
                if (a[i][j] == a[i - 1][j - 1] and cnt[vis[f(i, j)]] == 2)
                    corners[vis[f(i, j)]] += 2;
                if (a[i - 1][j] == a[i][j - 1] and cnt[vis[f(i, j - 1)]] == 2)
                    corners[vis[f(i, j - 1)]] += 2;
            }
        }
    }

    long long ans = 0;
    for (auto [a, c] : std::views::zip(area, corners))
        ans += 1LL * a * c;

    std::println("{}", ans);
}
