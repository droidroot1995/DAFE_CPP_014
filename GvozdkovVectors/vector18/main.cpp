#include "Vector.h"

void Print_vector(std::ostream &os, Vector &vec, const int n)
{
    for (int i = 0; i < n; ++i)
        os << vec[i] << ' ';
}



int main()
{
    Vector vector (10);

    for (int i = 0; i < vector.Size(); i++)
        {
            vector[i] = i;
        }

    Print_vector(std::cout, vector, vector.Size());

    return 0;
}
