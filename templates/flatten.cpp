#include <iostream>
#include <vector>


template<typename T>
class Array {
    std::vector<T> data;
public:
    Array() {}
    Array(size_t n, const T& value = T()) : data(n, value) {}

    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    size_t size() const { return data.size(); }

    
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};




template<typename T>
void flatten(const T& value, std::ostream& out) {
    out << value << " ";
}


template<typename T>
void flatten(const Array<T>& arr, std::ostream& out) {
    for (auto&& elem : arr) {
        flatten(elem, out); 
    }
}


int main() {
    Array<int> ints(2, 0); 
    ints[0] = 10; 
    ints[1] = 20; 
    //flatten(ints, std::cout); // выводит на экран строку "10 20"
    //Array< Array<int> > array_of_ints(2, ints); 
    //flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20" 
    Array<double> doubles(10, 0.0); 
    flatten(doubles, std::cout); // работать должно не только для типа int
    return 0;
}
