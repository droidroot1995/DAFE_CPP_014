
#ifndef CALCULATOR_ORL_VARIABLE_H
#define CALCULATOR_ORL_VARIABLE_H

#include "std_lib_facilities.h"


struct Variable
{
    string name;
    double value;
    bool is_const;

    Variable (bool c, string n, double v)  //конст или нет, название и значение
            : is_const{ c }, name{ n }, value{ v }
    { }
};


class Symbol_table
{
    vector<Variable> var_table;

public:
    double get(string s) const; //находит значение переменной

    void set(string s, double d); // присваивает значение переменной

    bool is_declared(string s) const; // меняет значение переменной

    double define(bool is_const, string var, double val); //проверяет, определена ли она
};
#endif //CALCULATOR_ORL_VARIABLE_H
