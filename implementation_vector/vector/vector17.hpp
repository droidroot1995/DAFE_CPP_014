#ifndef VECTOR17_HPP
#define VECTOR17_HPP
class Vector17
{
private:
    int sz;
    double *elem;
    
public:
    Vector17(int s);
    void set(int index, double value);
    double get(int index); 
    int size() const{ return sz;};
    void erase();
    ~Vector17() { delete[] elem; };
};


#endif