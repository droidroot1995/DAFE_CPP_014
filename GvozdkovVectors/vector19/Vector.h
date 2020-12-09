#pragma once
#include "std_lib_facilities.h"

template <typename T, typename A>
class VectorClass
{
public:
    int vector_size;
    T *element_pointer;
    int space;
    A alloc;

    VectorClass()
    {
        vector_size = 0;
        space = 0;
        element_pointer = nullptr;
    }

    VectorClass(A &a, int n);

    ~VectorClass();
};
