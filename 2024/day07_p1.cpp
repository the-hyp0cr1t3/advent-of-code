#include <bits/stdc++.h>

using i64 = long long;
namespace views = std::views;
namespace ranges = std::ranges;

template <typename T>
concept is_numeric = std::integral<T> || std::floating_point<T>;

template <is_numeric T>
std::vector<T> read(std::string_view s) {
    return s
        | views::split(' ')
        | views::transform([](auto &&w) {
            T x;
            std::from_chars(w.data(), w.data() + w.size(), x);
            return x;
        })
        | ranges::to<std::vector<T>>();
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    i64 ans = 0;

    int total_lines = 0;
    int max_n = 0, sum_n = 0;
    for (std::string line; std::getline(std::cin, line); total_lines++) {
        auto a = read<i64>(line);
        
        i64 target = a[0];
        a.erase(a.begin());

        int n = a.size() - 1;
        for (int m = 0; m < (1 << n); m++) {
            i64 x = a[0];
            for (int i = 0; i < n; i++) {
                if (m >> i & 1)
                    x += a[i + 1];
                else
                    x *= a[i + 1];
                if (x > target) break;
            }
            if (x == target) {
                ans += target;
                break;
            }
        }

        sum_n += n + 1;
        max_n = std::max(max_n, n + 1);
    }

    std::println("{}", ans);
    std::println(stderr, "read {} lines", total_lines);
    std::println(stderr, "sum n: {}", sum_n);
    std::println(stderr, "max n: {}", max_n);
}
