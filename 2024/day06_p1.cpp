#include <bits/stdc++.h>

std::array<int, 4> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line); )
        a.push_back(line);

    int n = a.size(), m = a[0].size(), x, y, d;
    std::println(stderr, "read {} x {} grid", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '^')
                x = i, y = j, d = 0;
            else if (a[i][j] == '>')
                x = i, y = j, d = 1;
            else if (a[i][j] == 'v')
                x = i, y = j, d = 2;
            else if (a[i][j] == '<')
                x = i, y = j, d = 3;
        }
    }

    while (true) {
        a[x][y] = '*';
        int nx = x + dx[d], ny = y + dy[d];
        if (!(0 <= nx and nx < n and 0 <= ny and ny < m))
            break;
        if (a[nx][ny] == '#')
            d = (d + 1) % 4;
        else
            x = nx, y = ny;
    }

    int ans = std::accumulate(
        a.begin(),
        a.end(),
        0,
        [] (int v, std::string_view s) {
            return v + std::ranges::count(s, '*');
        }
    );

    std::println("{}", ans);
}
