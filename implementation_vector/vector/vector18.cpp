#include "vector18.hpp"

Vector18::Vector18(int s)
    : sz{s}, elem{new double[sz]}
{
    for (int i = 0; i < sz; ++i)
    {
        elem[i] = 0.0;
    }
}

Vector18::Vector18(const Vector18 &v)
    : sz{v.size()}, elem{new double[sz]}
{
    for (int i = 0; i < sz; ++i)
    {
        elem[i] = v[i];
    }
}

Vector18::Vector18(std::initializer_list<double> ilt)
    : sz{(int)ilt.size()}, elem{new double[sz]}
{
    int i = 0;
    auto inter = ilt.begin();
    while (inter != ilt.end())
    {
        elem[i] = *inter;
        inter++;
        i++;
    }
}

Vector18::Vector18(Vector18 &&v)
    : sz{v.size()}, elem{v.elem}
{
    v.elem = nullptr;
    v.sz = 0;
}

Vector18::Vector18()
    : sz{0}, elem{nullptr} {}

int Vector18::size() const
{
    return sz;
}

void Vector18::erase()
{
    sz = 0;
    elem = nullptr;
}

Vector18 &Vector18::operator=(const Vector18 &v)
{
    sz = v.size();
    delete[] elem;
    elem = new double[sz];
    for (int i = 0; i < sz; ++i)
    {
        elem[i] = v[i];
    }
    return *this;
}

Vector18 &Vector18::operator=(Vector18 &&v)
{
    sz = v.size();
    elem = v.elem;
    v.erase();
    return *this;
}

double Vector18::operator[](int index) const
{
    return elem[index];
}

double &Vector18::operator[](int index)
{
    return elem[index];
}
