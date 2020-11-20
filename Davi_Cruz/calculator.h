#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "std_lib_facilities.h"
#include "token.cpp"
#include "variable.cpp"

struct Calculator
{
    bool open;
    ostream &os;
    Token_stream ts;
    Table_variables variables;

    Calculator(istream &is, ostream &os)
        : ts{Token_stream{is}}, os{os} {}
    
    Calculator()
        : ts{Token_stream{cin}}, os{cout} {}

    double primary();
    double expression();
    double term();
    double declaration();
    double statement();
    void clear_up_mess();
    void execute();
};

#endif