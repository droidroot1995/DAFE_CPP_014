#include "VectorClass.h"

template <typename T, typename A>
VectorClass<T, A>::VectorClass()
{
    vector_size = 0;
    space = 0;
    element_pointer = nullptr;
}


template <typename T, typename A>
VectorClass<T, A>::VectorClass(A &a, int n)
{
    alloc = a;
    element_pointer = a.allocate(n);
    vector_size = n;
    space = n;
}

template <typename T, typename A>
VectorClass<T, A>::~VectorClass()
{
    alloc.deallocate(element_pointer, space);
}
