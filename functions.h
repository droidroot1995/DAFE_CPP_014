#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include"Variable.h"
#include"Token_stream.h"

double expression ();
double primary ();
double term ();
double declaration (Token let_or_const);
double statement ();
void clean_up_mess ();
void printHelp();
void calculate ();
#endif // FUNCTIONS_H_INCLUDED
