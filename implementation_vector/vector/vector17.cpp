#include "vector17.hpp"

Vector17::Vector17(int s)
    : sz{s}, elem{new double[sz]}
{
    for (int i = 0; i < sz; ++i)
    {
        elem[i] = 0.0;
    }
}

void Vector17::set(int index, double value)
{
    elem[index] = value;
}

double Vector17::get(int index)
{
    return elem[index];
}

void Vector17::erase()
{
    for (int i = 0; i < sz; ++i)
    {
        elem[i] = 0.0;
    }
}