#include <bits/stdc++.h>

constexpr std::string_view kMul = "mul(", kDo = "do()", kDont = "don't()";

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

    std::vector<int> dos{-1};
    for (size_t i = 0; i != std::string::npos; ) {
        i = s.find(kDo, i);
        if (i != std::string::npos) {
            dos.push_back(i);
            i += kDo.length();            
        }
    }
    dos.push_back(s.length());

    std::vector<int> donts{-1};
    for (size_t i = 0; i != std::string::npos; ) {
        i = s.find(kDont, i);
        if (i != std::string::npos) {
            donts.push_back(i);
            i += kDont.length();
        }
    }
    donts.push_back(s.length());

    for (size_t i = 0, j = 1, k = 1; i < s.length(); ) {
        // mul(
        i = s.find(kMul, i);
        if (i == std::string::npos) break;
        i += kMul.length();

        while (dos[j] < (int)i) j++;
        while (donts[k] < (int)i) k++;

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

        if (dos[j - 1] >= donts[k - 1])
            ans += *x * *y;
    }

    std::println("{}", ans);
    std::println(stderr, "read {} lines", total_lines);
}
