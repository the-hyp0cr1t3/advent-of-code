#include <bits/stdc++.h>

constexpr int inf = 1e9;
constexpr int N = 71, K = 1024;

std::array<std::pair<int, int>, 4> dirs{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

int main() {
    std::array<std::array<int, N>, N> blocked_at;
    for (auto &x : blocked_at)
        x.fill(inf);

    int lines = 0;
    for (std::string line; std::getline(std::cin, line); lines++) {
        int x, y;
        std::sscanf(line.c_str(), "%d,%d", &y, &x);
        blocked_at[x][y] = std::min(blocked_at[x][y], lines + 1);
    }

    auto valid = [&](int x, int y, int t) {
        return 0 <= x and x < N and 0 <= y and y < N and blocked_at[x][y] > t;
    };

    auto bfs = [&](int stx, int sty, int t) {
        std::queue<std::pair<int, int>> q;
        std::vector d(N, std::vector<int>(N, -1));
        q.emplace(stx, sty);
        d[stx][sty] = 0;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;
                if (valid(nx, ny, t) and d[nx][ny] == -1) {
                    d[nx][ny] = d[x][y] + 1;
                    q.emplace(nx, ny);
                }
            }
        }
        return d[N - 1][N - 1];
    };

    std::println("{}", bfs(0, 0, K));
    std::println(stderr, "read {} lines", lines);
}
