#include <bits/stdc++.h>

using i64 = long long;
namespace views = std::views;
namespace ranges = std::ranges;

auto kmp(std::string s) {
    int n = s.length();
    std::vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 and s[i] != s[j])
            j = pi[j - 1];
        j += (s[i] == s[j]);
        pi[i] = j;
    }
    return pi;
}

int main() {
    using std::operator""sv;

    std::string line;
    std::getline(std::cin, line);
    auto patterns = line
        | views::split(", "sv)
        | ranges::to<std::vector<std::string>>();

    int m = patterns.size();
    std::println(stderr, "read {} patterns", m);
    
    int ans = 0;
    int designs = 0;
    std::getline(std::cin, line);
    for (std::string design; std::getline(std::cin, design); designs++) {
        int n = design.length();
        std::vector<std::vector<int>> matches(n + 1);
        for (const auto &pattern : patterns) {
            auto pi = kmp(pattern + '#' + design);
            for (int k = pattern.length(), i = 1; i <= n; i++)
                if (pi[i + k] == k) matches[i].push_back(k);
        }

        std::vector<i64> ways(n + 1);
        ways[0] = 1;
        for (int i = 1; i <= n; i++)
            for (auto k : matches[i])
                ways[i] += ways[i - k];

        ans += (ways[n] > 0);
    }

    std::println(stderr, "read {} designs", designs);
    std::println("{}", ans);
}
