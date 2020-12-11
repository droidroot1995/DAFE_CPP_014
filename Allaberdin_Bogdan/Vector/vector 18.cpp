#include<iostream>
class Vector {
    int vsize = 0;
    double* elements = nullptr;

public:
    Vector(int s):vsize{s}, elements{new double[s]}
    {
        for (int i(0); i < s; i++)
            elements[i] = 0;
    }

    Vector(std::initializer_list<double> lst):vsize{lst.size()}, elements{new double[vsize]}{
        std::copy(lst.begin(), lst.end(), elements);
    }

    Vector(const Vector& copy_vector):vsize{copy_vector.size()}, elements{new double[vsize]} {
        std::copy(copy_vector.elements, copy_vector.elements + vsize, elements);
    }

    Vector& operator=(const Vector& copy_vector){
        double *storage = new double[copy_vector.size()];
        std::copy(copy_vector.elements, copy_vector.elements + copy_vector.size(), storage);
        delete[] elements;
        elements = storage;
        vsize = copy_vector.size();
        return *this;
    }

    Vector(Vector&& transfer):vsize{transfer.size()}, elements{ transfer.elements} {
        transfer.vsize = 0;
        transfer.elements = nullptr;
    }

    Vector& operator=(Vector&& transfer){
        delete[] elements;
        elements = transfer.elements;
        vsize = transfer.size();
        transfer.elements = nullptr;
        transfer.vsize = 0;
        return *this;
    }

    double& operator[](int n){return elements[n];}
    double operator[](int n) const {return elements[n];};

    ~Vector() {delete[] elements;}



    int size() const {return vsize;}
};


int main(){

    return 0;
}

