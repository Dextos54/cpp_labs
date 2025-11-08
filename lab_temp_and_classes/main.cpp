#include <iostream>
#include <cassert>

template <typename T>
class Grid {
public:
    using size_type = unsigned;

private:
    T* data;
    size_type y_size;
    size_type x_size;

    class RowProxy {
        T* row_data;
        size_type x_size;
    public:
        RowProxy(T* row_data, size_type x_size)
            : row_data(row_data), x_size(x_size) {}

        T& operator[](size_type x) {
            return row_data[x];
        }

        const T& operator[](size_type x) const {
            return row_data[x];
        }
    };

public:
    Grid() : data(nullptr), y_size(0), x_size(0) {}

    Grid(const T& t) {
        y_size = 1;
        x_size = 1;
        data = new T[1];
        data[0] = t;
    }

    Grid(size_type y, size_type x) {
        y_size = y;
        x_size = x;
        data = new T[y * x];
    }

    Grid(size_type y, size_type x, const T& t) {
        y_size = y;
        x_size = x;
        data = new T[y * x];
        for (size_type i = 0; i < y * x; ++i)
            data[i] = t;
    }

    Grid(const Grid& other) {
        y_size = other.y_size;
        x_size = other.x_size;
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = other.data[i];
    }

    Grid(Grid&& other) noexcept {
        data = other.data;
        y_size = other.y_size;
        x_size = other.x_size;
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
    }

    // деструктор
    ~Grid() {
        delete[] data;
    }

    Grid& operator=(const Grid& other) {
        if (this != &other) {
            delete[] data;
            y_size = other.y_size;
            x_size = other.x_size;
            data = new T[y_size * x_size];
            for (size_type i = 0; i < y_size * x_size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    Grid& operator=(Grid&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            other.data = nullptr;
            other.y_size = 0;
            other.x_size = 0;
        }
        return *this;
    }

    Grid& operator=(const T& t) {
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = t;
        return *this;
    }

    T& operator()(size_type y, size_type x) {
        return data[y * x_size + x];
    }

    const T& operator()(size_type y, size_type x) const {
        return data[y * x_size + x];
    }

    RowProxy operator[](size_type y) {
        return RowProxy(data + y * x_size, x_size);
    }

    const RowProxy operator[](size_type y) const {
        return RowProxy(data + y * x_size, x_size);
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};

int main() {
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());
    using gsize_t = Grid<float>::size_type;
    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
    assert(0.0f == g[y_idx][x_idx]);
    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
    g[y_idx][x_idx] = 1.0f;
    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
    assert(1.0f == g(y_idx, x_idx));
    return 0;
}