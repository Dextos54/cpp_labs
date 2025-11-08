#include <iostream>

template<typename T, typename U>
struct is_same {
    static constexpr bool value = false;
};


template<typename T>
struct is_same<T, T> {
    static constexpr bool value = true;
};

int main() {
    std::cout <<  is_same<int, int>::value << "\n";
    std::cout << is_same<int, float>::value << "\n";
    std::cout << is_same<int, const int>::value << "\n";
}