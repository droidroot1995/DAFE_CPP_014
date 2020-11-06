#pragma once
#include"Variable.h"
#include"Token_stream.h"

double expression ();
double primary ();
double term ();
double declaration (Token let_or_const);
double statement ();
void ConstDeclaration();
void clean_up_mess ();
void printHelp();
void calculate ();
