#include "../vector/vector19.hpp"
#include <exception>

template <typename T, typename A>
Vector19<T, A>::Vector19(int s)
{
    if (s < 0)
        throw std::bad_alloc();
    elem = alloc.allocate(s);
    space = s;
    sz = s;
}

template <typename T, typename A>
Vector19<T, A>::Vector19(const Vector19<T, A> &v)
{
    elem = alloc.allocate(v.capacity());
    sz = v.size();
    space = v.capacity();
    for (int i = 0; i < sz; ++i)
        elem[i] = v[i];
}

template <typename T, typename A>
Vector19<T, A>::Vector19(std::initializer_list<T> ilt)
{
    sz = space = ilt.size();
    elem = alloc.allocate(space);
    int i = 0;
    auto inter = ilt.begin();
    while (inter != ilt.end())
    {
        elem[i] = *inter;
        inter++;
        i++;
    }
}

template <typename T, typename A>
Vector19<T, A>::Vector19(Vector19 &&v)
{
    sz = v.size();
    space = v.capacity();
    elem = v.elem;
}


template <typename T, typename A>
void Vector19<T, A>::push_back(T value)
{
    if (space == 0)
        reserve(8);
    else if (sz == space)
        reserve(2 * space);
    alloc.construct(&elem[sz], value);
    sz++;
}

template <typename T, typename A>
void Vector19<T, A>::reserve(int newalloc)
{
    if (newalloc < 0)
        throw std::bad_alloc();
    if (newalloc <= sz)
        throw std::bad_alloc();
    T *ptr = alloc.allocate(newalloc);
    for (int i = 0; i < sz; ++i)
        alloc.construct(&ptr[i], elem[i]);
    for (int i = 0; i < sz; ++i)
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem, space);
    elem = ptr;
    space = newalloc;
}

template <typename T, typename A>
void Vector19<T, A>::resize(int newsize)
{
    if (newsize <= sz)
        return;
    if (newsize <= space)
    {
        sz = newsize;
        return;
    }
    reserve(newsize);
    sz = newsize;
}
template <typename T, typename A>
int Vector19<T, A>::capacity() const
{
    return space;
}

template <typename T, typename A>
int Vector19<T, A>::size() const
{
    return sz;
}


template <typename T, typename A>
T &Vector19<T, A>::at(int n)
{
    if (n >= sz || n < 0)
        throw std::out_of_range("at");
    return elem[n];
}

template <typename T, typename A>
const T &Vector19<T, A>::at(int n) const
{

    if (n >= sz || n < 0)
        throw std::out_of_range("at");
    return elem[n];
}

template <typename T, typename A>
Vector19<T, A> &Vector19<T, A>::operator=(const Vector19<T, A> &v)
{
    T *ptr = alloc.allocate(v.capacity());
    for (int i = 0; i < v.size(); i++)
    {
        ptr[i] = v.at(i);
    }
    for (int i = 0; i < sz; ++i)
        alloc.destroy(&elem[i]);
    alloc.deallocate(elem, space);
    elem = ptr;
    sz = v.size();
    space = v.capacity();

    return *this;
}

template <typename T, typename A>
Vector19<T, A> &Vector19<T, A>::operator=(Vector19<T, A> &&v)
{
    space == v.capacity();
    sz = v.size();
    elem = v.elem;
    return *this;
}

template <typename T, typename A>
const T Vector19<T, A>::operator[](int index) const
{
    return elem[index];
}

template <typename T, typename A>
T &Vector19<T, A>::operator[](int index)
{
    return elem[index];
}

