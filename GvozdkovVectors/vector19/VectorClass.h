#pragma once
#include <iostream>
#include <std_lib_facilities.h>

template <typename T, typename A>
class VectorClass
{
public:
    int vector_size;
    T *element_pointer;
    int space;
    A alloc;

    VectorClass();

    VectorClass(A &a, int n);

    ~VectorClass();
};
