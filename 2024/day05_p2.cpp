#include <bits/stdc++.h>

using i64 = long long;
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

class Mapper {
    std::map<int, int> ids;
    std::vector<int> values;
public:
    int id(int x) {
        if (!ids.contains(x)) {
            ids[x] = size();
            values.push_back(x);
        }
        return ids[x];
    }
    int value(int x) const { return values[x]; }
    size_t size() const { return values.size(); }
};

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    Mapper mapper{};

    std::vector<std::pair<int, int>> edges;
    for (std::string line; std::getline(std::cin, line); ) {
        int x, y;
        if (std::sscanf(line.c_str(), "%d|%d", &x, &y) != 2)
            break;
        edges.emplace_back(mapper.id(x), mapper.id(y));
    }
    std::println(stderr, "{} edges scanned", edges.size());
    std::println(stderr, "{} vertices found", mapper.size());

    int n = mapper.size();

    int ans = 0, q = 0;
    for (std::string line; std::getline(std::cin, line); q++) {
        auto query = read<int>(line, ",")
            | views::transform([&](int u) { return mapper.id(u); })
            | ranges::to<std::vector<int>>();

        std::vector<bool> active(n);
        ranges::for_each(query, [&](int u) { active[u] = true; });

        std::vector d(n, std::vector<int>(n, 0));
        for (auto [x, y] : edges)
            if (active[x] and active[y]) d[x][y] = true;

        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    d[i][j] |= d[i][k] and d[k][j];

        auto sorted = query;
        ranges::stable_sort(sorted, [&](int i, int j) { return d[i][j]; });

        if (query != sorted)
            ans += mapper.value(sorted[sorted.size() / 2]);
    }
    std::println(stderr, "{} queries scanned", q);

    std::println("{}", ans);
}
