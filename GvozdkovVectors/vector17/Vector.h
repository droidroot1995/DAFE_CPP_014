#pragma once
#include <iostream>

class Vector {
    const int vector_size; //размер вектора меняться не должен
    double* element_pointer;

public:
    Vector(int s);

    ~Vector();

    int Size() const;

    double Get(int i) const;

    void Set(int i, double value);
};
