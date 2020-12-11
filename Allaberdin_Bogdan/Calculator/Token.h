#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <std_lib_facilities.h>

constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';

struct Token
{
  char kind;
  double value;
  string name;

  Token (char ch)
    : kind{ ch }, value{ 0 }
  { }

  Token (char ch, double val)
    : kind{ ch }, value{ val }
  { }
  Token(char ch, string n)
  : kind{ch}, name{n}
  { }
};

#endif // TOKEN_H_INCLUDED
