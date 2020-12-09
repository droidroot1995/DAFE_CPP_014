#include "Vector.h"

Vector::Vector(int s):vector_size{ s },
      element_pointer{new double[s]}
{
    for (int i = 0; i < s; ++i)
        element_pointer[i] = 0;
}

Vector::~Vector() { delete [] element_pointer; }

int Vector::Size() const { return vector_size; }

double Vector::Get(int i) const { return element_pointer[i]; }

void Vector::Set(int i, double value) { element_pointer[i] = value; }

