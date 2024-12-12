#include <bits/stdc++.h>

auto sum = [](int i, int l) {
    return 1LL * (i + l) * (i + l - 1) / 2 - 1LL * i * (i - 1) / 2;
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s;
    std::cin >> s;
    std::println(stderr, "read {} chars", s.length());

    if (s.length() % 2 == 0) s.pop_back();

    long long ans = 0;
    int i = s[0] - '0', f = 1, b = s.length() - 1;
    s[0] = '0';
    while (f < b) {
        int take = std::min(s[f] - '0', s[b] - '0');
        ans += b / 2 * sum(i, take);
        
        s[f] -= take;
        s[b] -= take;
        i += take;
        
        if (s[b] == '0') b -= 2;
        
        if (s[f] == '0') {
            f++;
            take = s[f] - '0';
            ans += f / 2 * sum(i, take);
            s[f] -= take;
            i += take;
            f++;
        }
    }

    std::println("{}", ans);
}
