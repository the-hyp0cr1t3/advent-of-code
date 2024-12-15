#include <bits/stdc++.h>

std::array<int, 4> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
constexpr std::string_view dir = "^>v<";

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line) and !line.empty(); )
        a.push_back(line);

    int n = a.size(), m = a[0].size(), x, y;
    std::println(stderr, "read {} x {} grid", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == '@') x = i, y = j;

    std::string moves;
    for (std::string line; std::getline(std::cin, line); )
        moves += line;
    std::println(stderr, "read {} robot moves", moves.length());

    auto valid = [&](int x, int y) {
        return 0 <= x and x < n and 0 <= y and y < m and a[x][y] != '#';
    };

    for (char c : moves) {
        int d = dir.find(c);
        int nx = x + dx[d], ny = y + dy[d];
        
        if (!valid(nx, ny)) continue;
        
        int fx = nx, fy = ny;
        while (valid(fx, fy) and a[fx][fy] == 'O')
            fx += dx[d], fy += dy[d];
        
        if (valid(fx, fy)) {
            std::swap(a[nx][ny], a[fx][fy]);
            std::swap(a[x][y], a[nx][ny]);
            x = nx, y = ny;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == 'O') ans += 100 * i + j;

    std::println("{}", ans);
}
