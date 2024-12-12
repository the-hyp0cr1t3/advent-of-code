#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<std::string> a;
    for (std::string line; std::getline(std::cin, line); )
        a.push_back(line);

    int n = a.size(), m = a[0].size();
    std::println(stderr, "read {} x {} grid", n, m);

    std::map<char, std::vector<std::pair<int, int>>> occ;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == '.') continue;
            occ[a[i][j]].emplace_back(i, j);
        }
    }

    std::vector antinode(n, std::vector<bool>(m, false));
    auto add_antinode = [&](std::pair<int, int> p, std::pair<int, int> q) {
        auto [a, b] = p;
        auto [c, d] = q;
        int dx = a - c, dy = b - d, g = std::gcd(dx, dy);
        dx /= g, dy /= g;
        for (int x = a, y = b;
                0 <= x and x < n and 0 <= y and y < m;
                    x += dx, y += dy)
            antinode[x][y] = true;
    };

    for (const auto &[c, v] : occ) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = i + 1; j < v.size(); j++) {
                add_antinode(v[i], v[j]);
                add_antinode(v[j], v[i]);
            }
        }
    }

    int ans = std::accumulate(
        antinode.begin(),
        antinode.end(),
        0,
        [] (int x, const auto &v) {
            return x + std::ranges::count(v, true);
        }
    );

    std::println("{}", ans);
}
