#include <bits/stdc++.h>

template <typename T>
using pq_gt = std::priority_queue<T, std::vector<T>, std::greater<T>>;

auto sum = [](int i, int l) {
    return 1LL * (i + l) * (i + l - 1) / 2 - 1LL * i * (i - 1) / 2;
};

int main() {
    std::string s;
    std::cin >> s;
    std::println(stderr, "read {} chars", s.length());

    if (s.length() % 2 == 1) s += '0';

    int n = s.length();

    int pos = 0;
    std::array<pq_gt<int>, 10> pockets{};
    for (int i = 0; i < n; i += 2) {
        pos += s[i] - '0';
        pockets[s[i + 1] - '0'].push(pos);
        pos += s[i + 1] - '0';
    }

    long long ans = 0;
    for (int i = n - 2; i >= 0; i -= 2) {
        pos -= s[i + 1] - '0';
        pos -= s[i] - '0';
        int leftmost_pos = pos, pocket = -1;
        for (int p = s[i] - '0'; p < 10; p++) {
            if (!pockets[p].empty()) {
                int f = pockets[p].top();
                if (f < leftmost_pos)
                    leftmost_pos = f, pocket = p;
            }
        }
        ans += i / 2 * sum(leftmost_pos, s[i] - '0');
        if (~pocket) {
            pockets[pocket].pop();
            pocket -= s[i] - '0';
            if (pocket > 0)
                pockets[pocket].push(leftmost_pos + s[i] - '0');
        }
    }

    std::println("{}", ans);
}
