#include <iostream>


template<typename T, typename...>
struct are_same {
    static constexpr bool value = true;
};


template<typename T, typename U, typename... Rest>
struct are_same<T, U, Rest...> {
    static constexpr bool value = std::is_same<T, U>::value && are_same<U, Rest...>::value;
};

int main() {
    std::cout << are_same<int, int, int>::value << "\n";   
    std::cout << are_same<int, float, int>::value << "\n";
    std::cout << are_same<double>::value << "\n";          
}