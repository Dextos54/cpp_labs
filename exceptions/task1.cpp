#include <iostream>
#include <string>
#include <stdexcept>


class MathException : public std::exception {
protected:
    std::string message;
public:
    MathException() : message("Ошибка") {}

    explicit MathException(const std::string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};


int divide(int x, int y) {
    if (y == 0)
        throw MathException("Деление на 0");
    return x / y;
}


int main() {
    try {
        std::cout << divide(10, 0) << std::endl;
    } catch (const MathException& e) {
        std::cerr << "Получена ошибка: " << e.what() << std::endl;
    }

    return 0;
}
