#ifndef VECTOR18_HPP
#define VECTOR18_HPP

#include <initializer_list>

class Vector18
{
private:
    int sz;
    double *elem;

public:
    explicit Vector18( int s);
    Vector18(const Vector18 &v);
    Vector18(std::initializer_list<double> ilt);
    Vector18(Vector18 &&v);
    Vector18();

    int size() const;
    void erase();

    Vector18 &operator=(const Vector18 &v);
    Vector18 &operator=(Vector18 &&v);
    double operator[](int index) const;
    double &operator[](int index);

    ~Vector18() { delete[] elem; };
};

#endif