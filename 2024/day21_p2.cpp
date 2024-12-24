#include <bits/stdc++.h>

using i64 = long long;
using pii = std::pair<int, int>;

constexpr int kRobots = 25;
constexpr i64 inf = 1e18;

std::array<int, 4> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
std::array<pii, 5> dirpad {{
    {0, 1}, // U
    {1, 2}, // R
    {1, 1}, // D
    {1, 0}, // L
    {0, 2}  // A
}};
std::array<pii, 11> numpad {{
    {3, 1}, // 0
    {2, 0}, // 1
    {2, 1}, // 2
    {2, 2}, // 3
    {1, 0}, // 4
    {1, 1}, // 5
    {1, 2}, // 6
    {0, 0}, // 7
    {0, 1}, // 8
    {0, 2}, // 9
    {3, 2}  // A
}};

template <size_t N>
auto calculate_moves(std::array<std::array<i64, 5>, 5> dp, const std::array<pii, N> &pad) {
    std::map<pii, int> padmap;
    for (int i = 0; i < N; i++)
        padmap[pad[i]] = i;

    std::array<std::array<i64, 5 * N>, 5 * N> d;
    for (int k = 0; k < 5 * N; k++) {
        d[k].fill(inf);
        d[k][k] = 0;
    }
    for (auto [k, p] : std::views::enumerate(pad)) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 4; j++) {
                auto q = std::make_pair(p.first + dx[j], p.second + dy[j]);
                if (padmap.contains(q))
                    d[5 * k + i][5 * padmap[q] + j] = dp[i][j];
            }
        }
    }

    for (int k = 0; k < 5 * N; k++)
        for (int i = 0; i < 5 * N; i++)
            for (int j = 0; j < 5 * N; j++)
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
    
    std::array<std::array<i64, N>, N> f;
    for (auto &x : f) x.fill(inf);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < 5; k++)
                f[i][j] = std::min(f[i][j], d[5 * i + 4][5 * j + k] + dp[k][4]);

    return f;
}

int main() {
    // dp[i][j] is number of human button presses to move
    // from i to j and click on j on some directional numpad
    std::array<std::array<i64, 5>, 5> dp;
    for (auto &x : dp) x.fill(1);

    for (int r = 0; r < kRobots; r++)
        dp = calculate_moves(dp, dirpad);

    auto d = calculate_moves(dp, numpad);

    i64 ans = 0;
    int lines = 0;
    for (std::string code; std::getline(std::cin, code); lines++) {
        int prv = 10;
        i64 moves = 0, num = 0;
        for (auto c : code) {
            int nxt = c == 'A' ? 10 : c - '0';
            if (nxt < 10) num = num * 10 + nxt;
            moves += d[prv][nxt];
            prv = nxt;
        }
        ans += num * moves;
    }

    std::println("{}", ans);
    std::println(stderr, "read {} codes", lines);
}
