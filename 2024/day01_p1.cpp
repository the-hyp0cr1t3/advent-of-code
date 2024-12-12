#include <bits/stdc++.h>
 
int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::vector<int> p, q;

    int total_lines = 0;
    for (std::string line; std::getline(std::cin, line); total_lines++) {
        int a, b;
        std::sscanf(line.c_str(), "%d %d", &a, &b);
        
        p.push_back(a);
        q.push_back(b);
    }

    std::ranges::sort(p);
    std::ranges::sort(q);

    long long ans = 0;
    for (int i = 0; i < total_lines; i++)
        ans += std::abs(p[i] - q[i]);

    std::println("{}", ans);
    std::println(stderr, "read {} lines", total_lines);
}
