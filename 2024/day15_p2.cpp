#include <bits/stdc++.h>

constexpr std::string_view dir = "^>v<";

std::array<int, 4> _dx = {-1, 0, 1, 0}, _dy = {0, 1, 0, -1};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line) and !line.empty(); ) {
        std::string expanded;
        for (auto c : line) {
            if (c == '@') expanded += "@.";
            else if (c == 'O') expanded += "[]";
            else if (c == '#') expanded += "##";
            else expanded += "..";
        }
        a.push_back(expanded);
    }

    int n = a.size(), m = a[0].size();
    std::println(stderr, "read {} x {} grid", n, m);

    std::string moves;
    for (std::string line; std::getline(std::cin, line); )
        moves += line;
    std::println(stderr, "read {} robot moves", moves.length());

    auto valid = [&](int x, int y) {
        return 0 <= x and x < n and 0 <= y and y < m and a[x][y] != '#';
    };

    auto push_horizontal = [&](this auto push, int x, int y, int dy, int width = 1) -> int {
        int ny = y + width * dy;
        if (!valid(x, ny)) return 0;

        if (a[x][ny] == '[' or a[x][ny] == ']')
            push(x, ny, dy, 2);

        if (a[x][ny] != '.') return 0;

        for (int w = width; w; w--)
            std::swap(a[x][y + w * dy], a[x][y + (w - 1) * dy]);
        return dy;
    };

    auto can_push_vertical = [&](this auto scout, int x, int y, int dx, int width = 1) -> bool {
        bool can = true;
        int nx = x + dx;
        for (int ny = y - 1; ny < y + width; ny++) {
            if (!valid(nx, ny) and y <= ny and ny < y + width)
                return false;
            if (!valid(nx, ny))
                continue;
            if (a[nx][ny] == '[')
                can &= scout(nx, ny, dx, 2);
        }
        return can;
    };

    auto push_vertical = [&](this auto push, int x, int y, int dx, int width = 1) -> void {
        int nx = x + dx;
        for (int ny = y - 1; ny < y + width; ny++)
            if (valid(nx, ny) and a[nx][ny] == '[')
                push(nx, ny, dx, 2);
        for (int w = 0; w < width; w++)
            std::swap(a[x][y + w], a[nx][y + w]);
    };

    int x, y;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == '@') x = i, y = j;

    for (char c : moves) {
        int d = dir.find(c);
        if (d & 1) {
            y += push_horizontal(x, y, _dy[d]);
        } else {
            if (can_push_vertical(x, y, _dx[d])) {
                push_vertical(x, y, _dx[d]);
                x += _dx[d];
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] == '[') ans += 100 * i + j;

    std::println("{}", ans);
}
