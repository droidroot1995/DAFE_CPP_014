#include "VectorClass.h"
#include "MyVector.h"







template <typename T>
void Print_vector(std::ostream &os, MyVector<T> &vec, const int n)
{
    for (int i = 0; i < n; ++i)
        os << vec[i] << ' ';

    os << endl;
}

int main()
{
    MyVector<int> vec1 = {1,2,3,4,5};
    MyVector<string> vec2 = {"Hello", "world", "!"};

    Print_vector(cout, vec1, vec1.Size());

    Print_vector(cout, vec2, vec2.Size());
}
