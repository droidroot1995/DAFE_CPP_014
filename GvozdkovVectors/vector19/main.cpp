#include <iostream>
#include "std_lib_facilities.h"

template <typename T, typename A>
class VectorClass
{
public:
    int vector_size;
    T *element_pointer;
    int space;
    A alloc;

    VectorClass()
    {
        vector_size = 0;
        space = 0;
        element_pointer = nullptr;
    }

    VectorClass(A &a, int n)
    {
        alloc = a;
        element_pointer = a.allocate(n);
        vector_size = n;
        space = n;
    }

    ~VectorClass()
    {
        alloc.deallocate(element_pointer, space);
    }
};


template <typename T, typename A = allocator<T>>
class MyVector: private VectorClass<T,A>
{
public:
    MyVector()
    {
        this->vector_size = 0;
        this->element_pointer = nullptr;
        this->space = 0;
    };

    MyVector(initializer_list<T> lst)
    {
        this->vector_size = lst.size();
        this->element_pointer = new T[this->vector_size];
        copy(lst.begin(), lst.end (), this->element_pointer);
    }

    explicit MyVector(int s)
    {
        this->vector_size =  s;
        this->space = s;
        this->element_pointer = new T[s];
    }

    int Size() { return this->vector_size; }

    ~MyVector() { delete[] this->element_pointer; }

    MyVector(const MyVector&);
    MyVector (MyVector&& );

    MyVector& operator= (const MyVector&);
    MyVector& operator= (MyVector&&);

    T& operator [] (int n) { return this->element_pointer[n]; }

    const T& operator [] (int n) const { return this->element_pointer[n]; }

    void reserve(int newalloc);

    int capacity () const
    {
        return this->space;
    }

    void resize(int newsize , T val = T());

    void push_back (const T& val);

    T& at (int n);

    const T& at (int n) const;
};

template <typename T, typename A>
MyVector<T, A>::MyVector(const MyVector& arg)
{
    this->vector_size = arg.vector_size;
    this->element_pointer = new T[arg.vector_size];
    copy(arg.element_pointer, arg.element_pointer+arg.vector_size, this->element_pointer);
}

template <typename T, typename A>
MyVector<T,A>&  MyVector<T,A>::operator = (const MyVector& a)
{
    if (this == &a)
        return *this;
    if (a.vector_size <= this->space)
    {
        for (int i = 0; i<a.vector_size; ++i)
            this->element_pointer[i] = a.element_pointer[i];
        this->vector_size = a.vector_size;
        return *this ;
    }

    T *p = new T [a.vector_size];

    for (int i = 0; i < a.vector_size; i++)
        p[i] = a.element_pointer[i];

    delete[] this->element_pointer;

    this->space = a.vector_size;
    this->element_pointer = p;

    return *this;
}

template <typename T, typename A>
MyVector<T,A>::MyVector (MyVector&& a)
{
    this->vector_size = a.vector_size;
    this->element_pointer = a.element_pointer;

    a.vector_size = 0;
    a.element_pointer = nullptr;
}

template <typename T, typename A>
MyVector<T,A>&  MyVector<T,A>::operator = (MyVector&& a)
{
    delete[] this->element_pointer;

    this->element_pointer = a.element_pointer;
    this->vector_size = a.vector_size;

    a.element_pointer = nullptr;
    a.vector_size = 0;

    return *this;
}

template <typename T, typename A>
void MyVector<T,A>::reserve (int newalloc)
{
    if (newalloc <= this->space)
        return;

    VectorClass<T,A> b(this->alloc, newalloc);

    uninitialized_copy(b.element_pointer, &b.element_pointer[this->vector_size],
            this->element_pointer);

    for (int i = 0; i < this->vector_size; i++)
        this->alloc.destroy(&this->element_pointer[i]);

    swap<VectorClass<T, A>>(*this, b);
}

template <typename T, typename A>
void MyVector<T,A>::resize (int newsize, T val)
{
    this->reserve(newsize);

    for (int i = this->vector_size ; i < newsize ; ++i)
        this->alloc.construct(&this->element_pointer[i], val);

    for (int i = this->vector_size ; i < newsize ; ++i)
        this->alloc.destroy(&this->element_pointer[i]);

    this->vector_size = newsize;
}

template <typename T, typename A>
void MyVector<T,A>::push_back (const T& val)
{
    if (this->space == 0)
        reserve(8);
    if (this->vector_size == this->space)
        reserve(2 * this->space);

    this->alloc.construct(&this->element_pointer[this->vector_size], val);
    this->vector_size++;
}

template <typename T, typename A>
T& MyVector<T,A>:: at (int n)
{
    if (n < 0 || this->vector_size <= n)
        throw out_of_range("Выход за диапазон значений");
    return this->element_pointer[n];
}

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
