#include <bits/stdc++.h>

constexpr std::string_view xmas = "XMAS";
constexpr std::pair<int, int> dir[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> grid;
    for (std::string line; std::getline(std::cin, line); )
        grid.push_back(line);

    int n = grid.size();
    int m = grid[0].length();

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (auto [dx, dy] : dir) {
                bool good = true;
                for (int k = 0; k < xmas.length(); k++) {
                    int x = i + k * dx;
                    int y = j + k * dy;
                    good &= (0 <= x and x < n and 0 <= y and y < m and grid[x][y] == xmas[k]);
                }
                ans += good;
            }
        }
    }

    std::println("{}", ans);
    std::println(stderr, "read {} lines", n);
}
