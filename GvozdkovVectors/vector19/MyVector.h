#pragma once
#include "VectorClass.h"

template <typename T, typename A = allocator<T>>
class MyVector: private VectorClass<T,A>
{
public:
    MyVector();

    MyVector(initializer_list<T> lst);

    explicit MyVector(int s)
    {
        this->vector_size =  s;
        this->space = s;
        this->element_pointer = new T[s];
    }

    int Size();

    MyVector(const MyVector&);
    MyVector (MyVector&& );

    ~MyVector();

    MyVector& operator= (const MyVector&);
    MyVector& operator= (MyVector&&);

    T& operator [] (int n) { return this->element_pointer[n]; }

    const T& operator [] (int n) const { return this->element_pointer[n]; }

    void reserve(int newalloc);

    int capacity () const;

    void resize(int newsize , T val = T());

    void push_back (const T& val);

    T& at (int n);

    const T& at (int n) const;
};

