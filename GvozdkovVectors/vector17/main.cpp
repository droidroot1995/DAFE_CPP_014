#include "Vector.h"

static void Print_vector(std::ostream &os, const Vector *vec, const int n)
{
    for (int i = 0; i < n; ++i)
        os << vec->Get(i) << ' ';
}



int main()
{
    Vector vector = Vector(10);
    int x = 100;

    for (int i = 0; i < vector.Size(); ++i)
        vector.Set(i, x++);

    Print_vector(std::cout, &vector, vector.Size());

    return 0;
}
