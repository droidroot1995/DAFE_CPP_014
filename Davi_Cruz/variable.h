#ifndef VARIABLE_H
#define VARIABLE_H

#include "std_lib_facilities.h"

struct Variable
{
    string name;
    double value;

    Variable(string name, double val)
        : name{name}, value{val} {}
};

struct Table_variables
{
    vector<Variable> variables{};

    Table_variables() {}

    double define_variable(string variable_name, double variable_value);

    double get_value(string variable_name);

    void set_value(string variable_name, double new_value);

    bool is_defined(string variable_name);
};

#endif