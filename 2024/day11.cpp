#include <bits/stdc++.h>

using i64 = long long;
constexpr int K = 2024, N = 75;

std::map<std::pair<i64, int>, i64> cache;

auto len = [](i64 x) {
    int d = 0;
    i64 p10 = 1;
    for (; x; x /= 10, d++)
        p10 *= (d & 1 ? 10 : 1);
    return std::make_pair(d, p10);
};

i64 get(i64 x, int t) {
    if (t == 0) return 1;
    auto s = std::make_pair(x, t);
    if (!cache.contains(s)) {
        if (x == 0) {
            cache[s] = get(1, t - 1);
        } else if (auto [d, p10] = len(x); d % 2 == 0) {
            cache[s] = get(x / p10, t - 1) + get(x % p10, t - 1);
        } else {
            cache[s] = get(x * K, t - 1);
        }
    }
    return cache[s];
}

int main() {
    std::string s;
    std::getline(std::cin, s);
    
    auto a = s
        | std::views::split(' ')
        | std::views::transform([](auto &&w) {
            i64 x;
            std::from_chars(w.data(), w.data() + w.size(), x);
            return get(x, N);
        });

    auto ans = std::ranges::fold_left(a, 0LL, std::plus<i64>());
    std::println("{}", ans);
}
