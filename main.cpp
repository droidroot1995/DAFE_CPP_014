#include <iostream>

using namespace std;

class vectop
{
protected:
    int sz;
    double* elem;
public:
    vectop(int s)
    {
        sz = s;
        elem = new double[sz];
        for(int i = 0; i < sz; ++i)
            elem[i] = 0.0;
    }
    int size() const
    {
        return sz;
    }
    vectop(initializer_list<double> l)
    {
        sz = l.size();
        elem = new double[sz];
        copy (l.begin (), l.end () , elem) ;
    }
    vectop (vectop&& a);
    vectop (const vectop&);

    vectop& operator = (const vectop&);
    vectop& operator = (vectop&&);
    double& operator [] (int n)
    {
        return elem[n];
    }
    double operator [] (int n) const;

    ~vectop()
    {
        delete[] elem;
    }
};

vectop::vectop (vectop&& a)
{
    sz = a.sz;
    elem = a.elem;
    a.sz = 0;
    a.elem = nullptr;
}

vectop::vectop(const vectop& arg)
{
    sz = arg.sz;
    elem = new double[sz];
    copy(arg.elem, arg.elem+arg.sz, elem);
}

vectop& vectop::operator = (const vectop& a)
{
    double *p = new double [a.sz];
    copy (a.elem, a.elem+a.sz ,p);
    delete [] elem;
    elem = p;
    sz = a.sz;
    return *this;
}

vectop& vectop::operator = (vectop&& a)
{
    delete[] elem;
    elem = a.elem;
    sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}

int main()
{
    vectop v1 (20);
    cout << "v1"<<'\n';
    for (int i = 0; i < v1.size(); i++)
    {
        v1[i] = i * i;
        cout << v1[i] << ' ';
    }
    cout<<'\n';

    cout << "======================================" << '\n';

    const vectop v2 = {1.2,2.5,3.5,4.8,5};
    v1 = v2;
    for (int i = 0; i < v1.size(); i++)
        cout<<v1[i]<<' ';
    return 0;
}
