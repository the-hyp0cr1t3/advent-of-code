#include <bits/stdc++.h>

std::array<std::pair<int, int>, 4> dir {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line); )
        a.push_back(line);

    int n = a.size(), m = a[0].size();
    std::println(stderr, "read {} x {} grid", n, m);

    std::vector<int> vis(n * m), ans(n * m);
    auto dfs = [&](this auto dfs, int x, int y) -> void {
        vis[x * m + y] = true;
        if (a[x][y] == '9') ans[x * m + y] = 1;
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!(0 <= nx and nx < n and 0 <= ny and ny < m and a[x][y] + 1 == a[nx][ny]))
                continue;
            if (!vis[nx * m + ny]) dfs(nx, ny);
            ans[x * m + y] += ans[nx * m + ny];
        }
    };

    long long total = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i * m + j]) dfs(i, j);
            total += (a[i][j] == '0') * ans[i * m + j];
        }
    }

    std::println("{}", total);
}
