#include <bits/stdc++.h>

constexpr std::string_view kMul = "mul(";

std::optional<int> find_int(std::string_view s, size_t &pos) {
    int x;
    auto [ptr, ec] = std::from_chars(s.data() + pos, s.data() + s.size(), x);
    if (ec == std::errc()) {
        pos = ptr - s.data();
        return std::optional<int>{x};
    } else {
        return std::nullopt;
    }
}

int main() {
    long long ans = 0;
    std::string s;

    int total_lines = 0;
    for (std::string line; std::getline(std::cin, line); total_lines++)
        s += line;
        
    for (size_t i = 0, j = 0, k = 0; i < s.length(); ) {
        // mul(
        i = s.find(kMul, i);
        if (i == std::string::npos) break;
        i += kMul.length();

        // x = \d+
        auto x = find_int(s, i);
        if (!x) continue;
        
        // ,
        if (i == s.length() or s[i] != ',')
            continue;
        i += 1;
        
        // y = \d+
        auto y = find_int(s, i);
        if (!y) continue;

        // )
        if (i == s.length() or s[i] != ')')
            continue;
        i += 1;

        ans += *x * *y;
    }

    std::println("{}", ans);
    std::println(stderr, "read {} lines", total_lines);
}
