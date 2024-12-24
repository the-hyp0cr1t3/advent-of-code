#include <bits/stdc++.h>

constexpr int inf = 1e9;
constexpr int kCheat = 2, kSave = 100;

std::array<std::pair<int, int>, 4> dirs{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

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

    auto valid = [&](int x, int y, bool cheat = false) {
        return 0 <= x and x < n and 0 <= y and y < m and (a[x][y] != '#' or cheat);
    };

    auto bfs = [&](int stx, int sty) {
        std::queue<std::pair<int, int>> q;
        std::vector d(n, std::vector<int>(m, inf));
        q.emplace(stx, sty);
        d[stx][sty] = 0;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;
                if (valid(nx, ny) and d[nx][ny] == inf) {
                    d[nx][ny] = d[x][y] + 1;
                    q.emplace(nx, ny);
                }
            }
        }
        return d;
    };

    auto S = bfs(sx, sy), E = bfs(ex, ey);

    int best = S[ex][ey], ans = 0;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            for (int dx = -kCheat; dx <= kCheat; dx++) {
                for (int dy = std::abs(dx) - kCheat; dy <= kCheat - std::abs(dx); dy++) {
                    int nx = x + dx, ny = y + dy;
                    if (!valid(nx, ny)) continue;
                    int t = S[x][y] + std::abs(dx) + std::abs(dy) + E[nx][ny];
                    if (best - t >= kSave)
                        ans++;
                }
            }
        }
    }

    std::println("{}", ans);
}
