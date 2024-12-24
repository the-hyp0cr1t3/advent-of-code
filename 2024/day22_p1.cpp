#include <bits/stdc++.h>

constexpr int N = 2000;
constexpr uint64_t mod = 16777216;

int main() {
    int buyers = 0;
    uint64_t ans = 0;
    for (std::string line; std::getline(std::cin, line); buyers++) {
        uint64_t x;
        std::from_chars(line.data(), line.data() + line.size(), x);
        for (int i = 0; i < N; i++) {
            (x ^= (x << 6)) %= mod;
            (x ^= (x >> 5)) %= mod;
            (x ^= (x << 11)) %= mod;
        }
        ans += x;
    }

    std::println("{}", ans);
    std::println(stderr, "read {} buyers", buyers);
}
