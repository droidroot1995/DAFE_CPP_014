#include <iostream>

using namespace std;

class vectop
        {
    int sz;
    double* elem;
public:
    vectop(int s)
    {
        sz = s;
        elem = new double[s];
        for(int i = 0; i < s; ++i)
            elem[i] = 0.0;
    }
    int size() const
    {
        return sz;
    }
    double getter(int n)
    {
        return elem[n];
    }
    void setter(int n, double v)
    {
        elem[n] = v;
    }
    ~vectop()
    {
        delete [] elem;
    }
};

int main()
{
    vectop v1(6);
    v1.setter(0,0.0);
    v1.setter(1,0.1);
    v1.setter(2,0.2);
    v1.setter(3,0.3);
    v1.setter(4,0.4);
    v1.setter(5,0.5);
    for (int i = 0; i < v1.size(); i++)
        cout << v1.getter(i) << '\n';
}
