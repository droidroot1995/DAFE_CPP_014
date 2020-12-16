#include "Vector.h"

Vector::Vector(int s):vector_size{ s },
      element_pointer{new double[s]}
{
    for (int i = 0; i < s; ++i)
        element_pointer[i] = 0;
}

int Vector::Size() const { return vector_size; }

Vector::Vector(std::initializer_list<double> l)
    {
        vector_size = l.size();
        element_pointer = new double[vector_size];
        std::copy(l.begin (), l.end (), element_pointer);
    }

Vector::~Vector() { delete [] element_pointer; }

Vector::Vector (Vector&& a)
{
    vector_size = a.vector_size;
    element_pointer = a.element_pointer;
    a.vector_size = 0;
    a.element_pointer = nullptr;
}

Vector::Vector(const Vector& arg)
{
    vector_size = arg.vector_size;
    element_pointer = new double[vector_size];
    std::copy(arg.element_pointer, arg.element_pointer+arg.vector_size, element_pointer);
}

Vector& Vector::operator = (const Vector& a)
{
    double *p = new double [a.vector_size];
    std::copy (a.element_pointer, a.element_pointer+a.vector_size ,p);
    delete [] element_pointer;
    element_pointer = p;
    vector_size = a.vector_size;
    return *this;
}

Vector& Vector::operator = (Vector&& a)
{
    delete[] element_pointer;
    element_pointer = a.element_pointer;
    vector_size = a.vector_size;
    a.element_pointer = nullptr;
    a.vector_size = 0;
    return *this;
}

double& Vector::operator [] (int i)
    {
        return element_pointer[i];
    }

