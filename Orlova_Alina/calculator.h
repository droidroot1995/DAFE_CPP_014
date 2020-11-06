#ifndef CALCULATOR_ORL_CALCULATOR_H
#define CALCULATOR_ORL_CALCULATOR_H

#include"variable.h"
#include"token.h"

double expression();
double primary();
double term();
double declaration(Token let_or_const);
double statement();
void clean_up_mess();
void printHelp();
void calculate();

#endif //CALCULATOR_ORL_CALCULATOR_H
