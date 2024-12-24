#include <bits/stdc++.h>

std::array<std::pair<int, int>, 4> dir {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

int main() {
    std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line); )
        a.push_back(line);

    int n = a.size(), m = a[0].size();
    std::println(stderr, "read {} x {} grid", n, m);

    std::vector<int> vis(n * m);
    auto dfs = [&](this auto dfs, int x, int y, int k) -> int {
        vis[x * m + y] = k;
        if (a[x][y] == '9') return 1;
        int ans = 0;
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!(0 <= nx and nx < n and 0 <= ny and ny < m and a[x][y] + 1 == a[nx][ny]))
                continue;
            if (vis[nx * m + ny] != k)
                ans += dfs(nx, ny, k);
        }
        return ans;
    };

    long long total = 0;
    for (int i = 0, k = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == '0') total += dfs(i, j, ++k);

    std::println("{}", total);
}
