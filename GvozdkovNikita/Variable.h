#pragma once
#include <Token.h>

class Variable
{
public:
    string name;
    double value;
    bool is_const;

    Variable (string n, double v, bool isconst)
        : name{ n }, value{ v }, is_const{ isconst }
    { }
};

class Symbol_table{
public:
    vector<Variable> var_table;
    double get_value (const string &s);
    void set_value (const string &s, const double &d);
    bool is_declared (const string &s);
    double define_name (const string &var, const double &val, const bool &con);
    void print_values();
};
