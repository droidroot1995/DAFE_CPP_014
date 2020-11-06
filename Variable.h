#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED

#include"Token.h"

struct Variable
{
  string name;
  double value;
  bool constant;
  Variable (string n, double v, bool c);
};

class Symbol_table{
private:
    vector<Variable> var_table;
public:
    double get_value (string s);
    void set_value (string s, double d);
    bool is_declared (string s);
    double define_name (string var, double val, bool con);
    void print_values();
};

#endif // VARIABLE_H_INCLUDED
