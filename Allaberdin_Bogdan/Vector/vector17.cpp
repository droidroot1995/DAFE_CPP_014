#include <iostream>
class Vector {
    int vsize = 0;
    double* elements = nullptr;

public:
    Vector(int s):vsize{s}, elements{new double[s]}
    {
        for (int i(0); i < s; i++)
            elements[i] = 0;
    }

    ~Vector() {delete[] elements;}

    int size() const {return vsize;}

    double get(int n) const {return elements[n];}

    void set(int n, double value) {elements[n] = value;}
};

void print_vector(std::ostream& os, const Vector *v);

int main(){
    Vector v1 = Vector(3);
    v1.set(0, 1);
    v1.set(1,4.3);
    print_vector(std::cout, &v1);
    return 0;
}

void print_vector(std::ostream& os, const Vector *v){
    for (int i(0); i < v->size(); i++)
        os << v->get(i) << " ";
}
