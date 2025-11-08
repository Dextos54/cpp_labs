#include <iostream>


template<typename Func, typename... Args>
auto invoke(Func f, Args... args) {
    return f(args...);
}


int foo(int a, int b, int c) {
    return a * a * a + b * b + c;
}

float bar(float r) {
    return 3.14f * r * r;
}

int main() {
    int r1 = invoke(foo, 1, 2, 3);      
    float r2 = invoke(bar, 1.0f);       

    std::cout << r1 << std::endl; // 8
    std::cout << r2 << std::endl; // 3.14

    return 0;
}