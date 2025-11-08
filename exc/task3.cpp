#include <string>
#include <sstream>
#include <exception>
#include <iostream>



class bad_from_string : public std::exception {
    std::string msg;
public:
    explicit bad_from_string(const std::string& s = "bad_from_string")
        : msg(s) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};


template <class T>
T from_string(const std::string& s)
{
    std::istringstream is(s);
    T value;

    is >> std::noskipws >> value;


    if (is.fail() || !is.eof())
        throw bad_from_string("bad_from_string: cannot convert \"" + s + "\"");

    return value;
}

int main() {
    using std::string;

    try {
    string s1("123");
    int    a1 = from_string<int>   (s1); // a1 = 123
    double b1 = from_string<double>(s1); // b1 = 123.0
    string c1 = from_string<string>(s1); // c1 = "123

    string s2("12.3");
    //int    a2 = from_string<int>   (s2); // исключение
    double b2 = from_string<double>(s2); // b2 = 12.3
    string c2 = from_string<string>(s2); // c2 = "12.3"

    string s3("abc");   
    //int    a3 = from_string<int>   (s3); // исключение
    //double b3 = from_string<double>(s3); // исключение
    string c3 = from_string<string>(s3); // c3 = "abc"


    } catch (const bad_from_string& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}