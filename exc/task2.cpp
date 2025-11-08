#include <iostream>

template <typename T>
class ControlBlock {
public:
    T* ptr;            
    size_t refCount;   

    ControlBlock(T* p) : ptr(p), refCount(1) {}

    ~ControlBlock() {
        delete ptr;
    }
};


template <typename T>
class SharedPtr {
private:
    ControlBlock<T>* control; 

    
    SharedPtr(ControlBlock<T>* cb) : control(cb) {}

public:
    
    template <typename U, typename... Args>
    friend SharedPtr<U> make_shared(Args&&... args);

    // Конструктор по умолчанию
    SharedPtr() : control(nullptr) {}

    // Конструктор от обычного указателя
    explicit SharedPtr(T* ptr) {
        control = new ControlBlock<T>(ptr);
    }

    // Конструктор копирования
    SharedPtr(const SharedPtr& other) {
        control = other.control;
        if (control)
            control->refCount++;
    }

    
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            control = other.control;
            if (control)
                control->refCount++;
        }
        return *this;
    }

    
    ~SharedPtr() {
        release();
    }

    
    void release() {
        if (control) {
            control->refCount--;
            if (control->refCount == 0)
                delete control; 
            control = nullptr;
        }
    }

    
    size_t use_count() const {
        return control ? control->refCount : 0;
    }

    
    T* get() const {
        return control ? control->ptr : nullptr;
    }

    T& operator*() const { return *(control->ptr); }
    T* operator->() const { return control->ptr; }
};


template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    T* obj = new T(std::forward<Args>(args)...);
    ControlBlock<T>* block = new ControlBlock<T>(obj);
    return SharedPtr<T>(block);
}


struct Foo {
    int x;
    Foo(int val) : x(val) {
        std::cout << "Создан\n";
    }
    ~Foo() {
        std::cout << "Уничтожен\n";
    }
};

int main() {
    {
        auto p1 = make_shared<Foo>(1);
        std::cout << p1.use_count() << "\n";

        {
            auto p2 = p1; 
            std::cout << p1.use_count() << "\n";
            std::cout << p2->x << "\n";
        }

        std::cout << p1.use_count() << "\n";
    } 

    return 0;
}
