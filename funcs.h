#ifndef FUNCS_H
#define FUNCS_H

#include"Variable.h"
#include"Token_stream.h"

double expression();
double primary();
double term();
double declaration(Token let_or_const);
double statement();
void clean_up_mess();
void printHelp();
void calculate();

#endif // FUNCS_H
