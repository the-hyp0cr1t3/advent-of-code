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
    auto check_valid = [&](const auto &order) -> bool {
        std::vector<bool> active(n);
        ranges::for_each(order, [&](int u) { active[u] = true; });

        std::vector<std::vector<int>> rg(n);
        for (auto [x, y] : edges)
            if (active[x] and active[y])
                rg[y].emplace_back(x);

        std::vector<bool> vis(n);
        auto dfs = [&](this auto dfs, int u) -> void {
            vis[u] = true;
            for (int v : rg[u])
                if (!vis[v]) dfs(v);
        };
        for (int u : order) {
            if (vis[u]) return false;
            dfs(u);
        }
        return true;
    };

    int ans = 0, q = 0;
    for (std::string line; std::getline(std::cin, line); q++) {
        auto query = read<int>(line, ",")
            | views::transform([&](int u) { return mapper.id(u); })
            | ranges::to<std::vector<int>>();

        if (check_valid(query))
            ans += mapper.value(query[query.size() / 2]);
    }
    std::println(stderr, "{} queries scanned", q);

    std::println("{}", ans);
}
