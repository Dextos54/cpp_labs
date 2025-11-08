#include <iostream>
#include <cassert>
#include <utility>

template <typename T, unsigned N>
class Grid;

template <typename T>
class Grid<T, 1> {
public:
    using size_type = unsigned;

private:
    T* data;
    size_type size;

public:
    Grid() : data(nullptr), size(0) {}
    
    Grid(size_type n)
        : data(new T[n]), size(n) {}

    Grid(size_type n, const T& value)
        : data(new T[n]), size(n) {
        for (size_type i = 0; i < size; ++i)
            data[i] = value;
    }

    Grid(const T& value)
        : data(new T[1]), size(1) {
        data[0] = value;
    }
    Grid(const Grid& other)
        : data(new T[other.size]), size(other.size) {
        for (size_type i = 0; i < size; ++i)
            data[i] = other.data[i];
    }
    Grid(Grid&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }
    ~Grid() { delete[] data; }
    Grid& operator=(const Grid& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (size_type i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
    Grid& operator=(Grid&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    Grid& operator=(const T& value) {
        for (size_type i = 0; i < size; ++i)
            data[i] = value;
        return *this;
    }
    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }
    T& operator()(size_type i) { return data[i]; }
    const T& operator()(size_type i) const { return data[i]; }
    size_type get_size() const { return size; }
};

template <typename T, unsigned N>
class Grid {
public:
    using size_type = unsigned;

private:
    Grid<T, N - 1>* data;
    size_type size;

public:

    Grid() : data(nullptr), size(0) {}

    Grid(size_type n)
        : data(new Grid<T, N - 1>[n]), size(n) {}

    template <typename... Args>
    Grid(size_type n, Args... rest)
        : data(new Grid<T, N - 1>[n]), size(n) {
        for (size_type i = 0; i < size; ++i)
            data[i] = Grid<T, N - 1>(rest...);
    }
    Grid(const T& value)
        : data(new Grid<T, N - 1>[1]), size(1) {
        data[0] = Grid<T, N - 1>(value);
    }
    Grid(const Grid& other)
        : data(new Grid<T, N - 1>[other.size]), size(other.size) {
        for (size_type i = 0; i < size; ++i)
            data[i] = other.data[i];
    }


    Grid(Grid&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    ~Grid() { delete[] data; }

    Grid& operator=(const Grid& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new Grid<T, N - 1>[size];
            for (size_type i = 0; i < size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }
    Grid& operator=(Grid&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    Grid& operator=(const T& value) {
        for (size_type i = 0; i < size; ++i)
            data[i] = value;
        return *this;
    }

    template <typename... Args>
    auto& operator()(size_type i, Args... rest) {
        return data[i](rest...);
    }

    template <typename... Args>
    const auto& operator()(size_type i, Args... rest) const {
        return data[i](rest...);
    }

    Grid<T, N - 1>& operator[](size_type i) { return data[i]; }
    const Grid<T, N - 1>& operator[](size_type i) const { return data[i]; }
    size_type get_size() const { return size; }
};

int main() {
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));
    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));
    g2 = g3[1];
    assert(1.0f == g2(1, 1));
    return 0;
}
