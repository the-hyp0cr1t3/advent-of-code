#include <bits/stdc++.h>

constexpr int M = 101, N = 103, duration = 100;
std::array<std::array<int, M>, N> count;

int total(int lx, int rx, int ly, int ry) {
    int t = 0;
    for (int i = lx; i < rx; i++)
        for (int j = ly; j < ry; j++)
            t += count[i][j];
    return t;
}

int main() {
    int lines = 0;
    for (std::string line; std::getline(std::cin, line); lines++) {
        int px, py, vx, vy;
        std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
        py = ((py + duration * vy) % N + N) % N;
        px = ((px + duration * vx) % M + M) % M;
        count[py][px]++;
    }

    long long ans = 1;
    for (int lx : {0, N / 2 + 1})
        for (int ly : {0, M / 2 + 1})
            ans *= total(lx, lx + N / 2, ly, ly + M / 2);

    std::println("{}", ans);
    std::println(stderr, "read {} lines", lines);
}
