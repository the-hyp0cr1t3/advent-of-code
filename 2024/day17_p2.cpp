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

int run(i64 A, i64 B, i64 C, std::vector<int> program) {
    auto val = [&](int k) -> int {
        return k < 4 ? k : k == 4 ? A : k == 5 ? B : C;
    };

    for (int ip = 0; ip + 1 < program.size(); ip += 2) {
        int op = program[ip];
        int k = op == 1 or op == 3 ? program[ip + 1] : val(program[ip + 1]);
        if (op == 0) {
            A >>= k;
        } else if (op == 1) {
            B ^= k;
        } else if (op == 2) {
            B = k & 7;
        } else if (op == 3) {
            if (A != 0) ip = k - 2;
        } else if (op == 4) {
            B ^= C;
        } else if (op == 5) {
            return k & 7;
        } else if (op == 6) {
            B = A >> k;
        } else if (op == 7) {
            C = A >> k;
        }
    }
    assert(false);
}

i64 recur(i64 A, i64 B, i64 C, const std::vector<int> &program, int cur) {
    if (cur == -1) return A;
    
    for (int i = 0; i < 8; i++) {
        i64 nA = (A << 3) | i;
        if (run(nA, B, C, program) == program[cur]) {
            auto ans = recur(nA, B, C, program, cur - 1);
            if (~ans) return ans;
        }
    }

    return -1;
}

int main() {
    using std::operator""sv;

    std::string line;
    i64 A, B, C;
    std::getline(std::cin, line);
    std::sscanf(line.c_str(), "Register A: %lld", &A);
    std::getline(std::cin, line);
    std::sscanf(line.c_str(), "Register B: %lld", &B);
    std::getline(std::cin, line);
    std::sscanf(line.c_str(), "Register C: %lld", &C);

    std::getline(std::cin, line);
    std::getline(std::cin, line);
    auto program = read<int>(line.substr(9), ","sv);

    A = recur(0, B, C, program, program.size() - 1);
    assert(A != -1);
    std::println("{}", A);
}
