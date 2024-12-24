#include <bits/stdc++.h>

constexpr int N = 2000;
constexpr uint64_t mod = 16777216;

int main() {
    std::map<int, int> cand;

    int buyers = 0;
    for (std::string line; std::getline(std::cin, line); buyers++) {
        uint64_t x;
        std::from_chars(line.data(), line.data() + line.size(), x);

        std::vector<uint64_t> a{x};
        for (int i = 0; i < N; i++) {
            (x ^= (x << 6)) %= mod;
            (x ^= (x >> 5)) %= mod;
            (x ^= (x << 11)) %= mod;
            a.push_back(x);
        }

        std::map<int, int> seen;
        for (int i = 4; i <= N; i++) {
            int h = 0;
            for (int j = i; j > i - 4; j--)
                h = 23 * h + (a[j] % 10 - a[j - 1] % 10 + 10);
            if (!seen.contains(h))
                seen[h] = a[i] % 10;
        }

        for (auto [h, v] : seen)
            cand[h] += v;
    }

    int best = 0;
    for (auto [h, v] : cand)
        best = std::max(best, v);

    std::println("{}", best);
    std::println(stderr, "read {} buyers", buyers);
}
