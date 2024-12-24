#include <bits/stdc++.h>

int main() {
    std::vector<std::string> grid;
    for (std::string line; std::getline(std::cin, line); )
        grid.push_back(line);

    int n = grid.size();
    int m = grid[0].length();

    auto is_ms = [&](int a, int b, int c, int d) {
        return grid[a][b] == 'M' and grid[c][d] == 'S'
                or grid[a][b] == 'S' and grid[c][d] == 'M';
    };

    int ans = 0;
    for (int i = 1; i + 1 < n; i++) {
        for (int j = 1; j + 1 < m; j++) {
            ans += grid[i][j] == 'A'
                    and is_ms(i - 1, j - 1, i + 1, j + 1)
                    and is_ms(i - 1, j + 1, i + 1, j - 1);
        }
    }

    std::println("{}", ans);
    std::println(stderr, "read {} lines", n);
}
