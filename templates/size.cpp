#include <iostream>

template<typename T, unsigned N>
struct Array {
    T data[N];
};

template<typename T, unsigned N>
unsigned size(const Array<T, N>& arr) {
    return N;
}

int main() {
    unsigned s1 = size(Array<int, 10>{});   
    Array<float, 100> arr;
    unsigned s2 = size(arr);                

    std::cout << s1 << " " << s2 << "\n";   // 10 100
}