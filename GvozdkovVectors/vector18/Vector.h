#pragma once
#include <iostream>

class Vector {
    int vector_size; 
    double* element_pointer;

public:
    Vector(int s);

    ~Vector();

    int Size() const;

    Vector(std::initializer_list<double> l);

    Vector (Vector&& a);
    Vector (const Vector&);

    Vector& operator = (const Vector&);
    Vector& operator = (Vector&&);
    double& operator [] (int n);
    double operator [] (int n) const;
};
