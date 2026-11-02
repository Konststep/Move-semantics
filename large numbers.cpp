#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class big_integer {
    std::vector<int> V;

public:
    explicit big_integer(const std::string& num) {
        if (num.empty()) {
            V = { 0 };
            return;
        }
        for (int i = static_cast<int>(num.size()) - 1; i >= 0; i--)
            V.push_back(num[i] - '0');
    }

    big_integer() : V{0} {}

    big_integer(big_integer&& other) noexcept : V(std::move(other.V)) {}

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other)
            V = std::move(other.V);
        return *this;
    }

    big_integer operator+(const big_integer& num2) const {
        big_integer rez;
        rez.V.clear();
        int transfer = 0;
        size_t n = std::max(V.size(), num2.V.size());

        for (size_t i = 0; i < n || transfer; i++) {
            int sum = transfer;
            if (i < V.size()) sum += V[i];
            if (i < num2.V.size()) sum += num2.V[i];
            rez.V.push_back(sum % 10);
            transfer = sum / 10;
        }
        return rez;
    }

    big_integer operator*(int m) const {
        if (m == 0) return big_integer("0");

        big_integer rez;
        rez.V.clear();
        long long transfer = 0;

        for (size_t i = 0; i < V.size() || transfer; ++i) {
            long long mult = transfer;
            if (i < V.size())
                mult += static_cast<long long>(V[i]) * m;

            rez.V.push_back(static_cast<int>(mult % 10));
            transfer = mult / 10;
        }
        return rez;
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& a) {
        for (auto it = a.V.rbegin(); it != a.V.rend(); it++)
            os << *it;
        return os;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << "\n"; // 193099

    auto result1 = number1 * 123;
    std::cout << result1 << "\n"; // 14092725

    return 0;
}