#include <bits/stdc++.h>

using i64 = long long;

bool read(i64 &a, i64 &b, i64 &c, i64 &f, i64 &g, i64 &h) {
    std::string line;

    do {
        if (!std::getline(std::cin, line)) return false;
    } while (line.empty());
    std::sscanf(line.c_str(), "Button A: X%lld, Y%lld", &a, &f);

    do {
        if (!std::getline(std::cin, line)) return false;
    } while (line.empty());
    std::sscanf(line.c_str(), "Button B: X%lld, Y%lld", &b, &g);

    do {
        if (!std::getline(std::cin, line)) return false;
    } while (line.empty());
    std::sscanf(line.c_str(), "Prize: X=%lld, Y=%lld", &c, &h);

    return true;
}

i64 solve(i64 a, i64 b, i64 c, i64 f, i64 g, i64 h) {
    if ((c * g - b * h) % (a * g - b * f))
        return 0;
    i64 x = (c * g - b * h) / (a * g - b * f);

    if ((a * h - c * f) % (a * g - b * f))
        return 0;
    i64 y = (a * h - c * f) / (a * g - b * f);

    if (x < 0 or y < 0)
        return 0;

    return 3 * x + y;
}

int main() {
    i64 ans = 0;

    int cases = 0;
    i64 a, b, c, f, g, h;
    for (; read(a, b, c, f, g, h); cases++)
        ans += solve(a, b, c, f, g, h);

    std::println("{}", ans);
    std::println(stderr, "read {} cases", cases);
}
