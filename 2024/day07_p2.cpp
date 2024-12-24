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

auto pow10 = [](i64 x) {
    i64 p = 1;
    while (x) p *= 10, x /= 10;
    return p;
};

int main() {
    i64 ans = 0;

    int total_lines = 0;
    int max_n = 0, sum_n = 0;
    for (std::string line; std::getline(std::cin, line); total_lines++) {
        auto a = read<i64>(line);
        
        i64 target = a[0];
        a.erase(a.begin());

        int n = a.size() - 1;

        int N = 1;
        for (int i = 0; i < n; i++)
            N *= 3;

        for (int m = 0; m < N; m++) {
            i64 x = a[0];
            for (int i = 0, p = m; i < n; i++, p /= 3) {
                if (p % 3 == 0)
                    x += a[i + 1];
                else if (p % 3 == 1)
                    x *= a[i + 1];
                else
                    x = x * pow10(a[i + 1]) + a[i + 1];
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
