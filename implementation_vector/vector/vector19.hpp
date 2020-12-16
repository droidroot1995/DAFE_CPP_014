#ifndef VECTOR19_HPP
#define VECTOR19_HPP

#include <initializer_list>
#include <memory>

template <typename T, typename A = std::allocator<T>>
class Vector19
{
private:
    unsigned int sz;
    unsigned int space;
    A alloc;
    T *elem;

public:
    explicit Vector19(int s);
    Vector19(const Vector19 &v);
    Vector19(std::initializer_list<T> ilt);
    Vector19(Vector19 &&v);
    Vector19() : sz{0}, space{0},elem{alloc.allocate(0)} {};

    void push_back(T value);
    void reserve(int newalloc);
    void resize(int newsize);
    int capacity() const;
    int size() const;
    T &at(int n);
    const T &at(int n) const;

    Vector19 &operator=(const Vector19 &v);
    Vector19 &operator=(Vector19 &&v);
    const T operator[](int index) const;
    T &operator[](int index);

    ~Vector19() { alloc.deallocate(elem, space); };
};

#endif