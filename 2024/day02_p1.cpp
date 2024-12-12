#include <bits/stdc++.h>

namespace views = std::views;
namespace ranges = std::ranges;

template <typename T>
concept is_numeric = std::integral<T> || std::floating_point<T>;

template <is_numeric T>
std::vector<T> read(std::string_view s, std::string_view delim = " ") {
    return s
        | views::split(delim)
        | views::transform([](auto &&w) {
            T x;
            std::from_chars(w.data(), w.data() + w.size(), x);
            return x;
        })
        | ranges::to<std::vector<T>>();
}

bool is_good(auto &&r) {
    if (r.empty()) return true;

    if (!ranges::is_sorted(r) and !ranges::is_sorted(r, ranges::greater{}))
        return false;
    
    std::vector<int> diffs;
    std::adjacent_difference(r.begin(), r.end(), std::back_inserter(diffs));
    auto d = diffs
        | views::drop(1)
        | views::transform([](auto i) { return std::abs(i); });

    return 0 < *ranges::min_element(d) and *ranges::max_element(d) <= 3;
}
 
int main() {
    int ans = 0;

    int total_lines = 0;
    for (std::string line; std::getline(std::cin, line); total_lines++)
        ans += is_good(read<int>(line));

    std::println("{}", ans);
    std::println(stderr, "read {} lines", total_lines);
}
