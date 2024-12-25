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

auto run(int A, int B, int C, std::vector<int> program) {
    auto val = [&](int k) -> int {
        return k < 4 ? k : k == 4 ? A : k == 5 ? B : C;
    };

    std::vector<int> output;
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
            output.push_back(k & 7);
        } else if (op == 6) {
            B = A >> k;
        } else if (op == 7) {
            C = A >> k;
        }
    }

    return output;
}

int main() {
    using std::operator""sv;

    std::string line;
    int A, B, C;
    std::getline(std::cin, line);
    std::sscanf(line.c_str(), "Register A: %d", &A);
    std::getline(std::cin, line);
    std::sscanf(line.c_str(), "Register B: %d", &B);
    std::getline(std::cin, line);
    std::sscanf(line.c_str(), "Register C: %d", &C);

    std::getline(std::cin, line);
    std::getline(std::cin, line);
    auto program = read<int>(line.substr(9), ","sv);

    auto output = run(A, B, C, program);
    for (int i = 0; i < output.size(); i++)
        std::print("{}{}", output[i], ",\n"[i + 1 == output.size()]);
}
