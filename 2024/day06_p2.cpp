#include <bits/stdc++.h>

std::array<int, 4> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line); )
        a.push_back(line);

    int n = a.size(), m = a[0].size(), sx, sy, sd;
    std::println(stderr, "read {} x {} grid", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '^')
                sx = i, sy = j, sd = 0;
            else if (a[i][j] == '>')
                sx = i, sy = j, sd = 1;
            else if (a[i][j] == 'v')
                sx = i, sy = j, sd = 2;
            else if (a[i][j] == '<')
                sx = i, sy = j, sd = 3;
        }
    }

    auto f = [&](int x, int y, int d) {
        return 4 * (m * x + y) + d;
    };

    std::vector<int> cycle(4 * n * m, -1);
    auto dfs = [&](this auto dfs, int x, int y, int d) -> int {
        cycle[f(x, y, d)] = 1;

        int nx = x + dx[d], ny = y + dy[d], nd = d;
        if (!(0 <= nx and nx < n and 0 <= ny and ny < m))
            return cycle[f(x, y, d)] = 0;

        if (a[nx][ny] == '#')
            nx = x, ny = y, nd = (d + 1) % 4;

        return cycle[f(x, y, d)] = ~cycle[f(nx, ny, nd)]
                                        ? cycle[f(nx, ny, nd)] : dfs(nx, ny, nd);
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '#' or i == sx and j == sy)
                continue;
            a[i][j] = '#';
            ans += dfs(sx, sy, sd);
            a[i][j] = '.';
            std::ranges::fill(cycle, -1);
        }
    }

    std::println("{}", ans);
}
