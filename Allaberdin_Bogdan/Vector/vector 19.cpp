#include<iostream>

#include <std_lib_facilities.h>
template<typename T, typename A = std::allocator<T>> class _Vector {
    A alloc;
    int vsize;
    T *elements;
    int space;
public:
    _Vector(): vsize{0}, elements{nullptr}, space{0} {}

     T& at(int n){
        if (n < 0 || vsize <= n) throw out_of_range();
        return elements[n];
    }
    const T& at(int n) const{
        if (n < 0 || vsize <= n) throw out_of_range();
        return elements[n];
    }

    explicit _Vector(int s):vsize{s}, elements{new T[s]}, space{s}
    {
        for (int i(0); i < s; i++)
            elements[i] = 0;
    }

    _Vector(std::initializer_list<T> lst):vsize{lst.size()}, elements{new T[vsize]}, space{lst.size()}{
        std::copy(lst.begin(), lst.end(), elements);
    }

    _Vector(const _Vector& copy_vector):vsize{copy_vector.size()}, elements{new T[vsize]}, space{copy_vector.capacity()} {
        std::copy(copy_vector.elements, copy_vector.elements + vsize, elements);
    }

    _Vector& operator=(const _Vector& copy_vector){
        if (this == &copy_vector) return *this;

        if (copy_vector.size() <= space){
            for (int i(0); i < copy_vector.size(); i++)
                elements[i] = copy_vector.elements[i];
            vsize = copy_vector.size();
            return *this;
        }

        T *storage = new T[copy_vector.size()];
        for (int i(0); i < copy_vector.size(); i++)
            storage[i] = copy_vector.elements[i];
        delete[] elements;
        elements = storage;
        space = vsize = copy_vector.size();
        return *this;
    }

    _Vector(_Vector&& transfer):vsize{transfer.size()}, elements{ transfer.elements}, space{transfer.capacity()} {
        transfer.vsize = 0;
        transfer.space = 0;
        transfer.elements = nullptr;
    }

    _Vector& operator=(_Vector&& transfer){
        delete[] elements;
        elements = transfer.elements;
        vsize = transfer.size();
        space = transfer.capacity();
        transfer.elements = nullptr;
        transfer.vsize = 0;
        transfer.space = 0;
        return *this;
    }


    T& operator[](int n){return elements[n];}
    T operator[](int n) const {return elements[n];};

    ~_Vector() {delete[] elements;}

    void reserve(int newalloc){
        if (newalloc <= space) return;
        T *storage = alloc.allocate(newalloc);
        for (int i(0); i < vsize; i++)
            alloc.construct(&storage[i],elements[i]);
        for (int i(0); i < vsize; i++)
            alloc.destroy(&elements[i]);
        alloc.deallocate(elements, space);
        elements = storage;
        space = newalloc;
    }

    void resize(int newsize, T val = T()){
        reserve(newsize);
        for (int i(vsize); i < newsize; i++)
            alloc.construct(&elements[i], val);
        for (int i(vsize); i < newsize; i++)
            alloc.destroy(&elements[i]);
        vsize = newsize;
    }

    void push_back(const T& val){
        if (space == 0)
            reserve(8);
        else if (vsize == space)
            reserve(2*space);
        alloc.construct(&elements[vsize], val);
        vsize++;
    }

    int size() const {return vsize;}
    int capacity() const {return space;}

};
int main(){}
