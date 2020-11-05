#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H

#include "Token.h"

class Token_stream
{
private:
  bool full{ false };
  Token buffer{ '\0' };
public:
  Token_stream () { }
  Token get ();
  void putback (Token t);
  void ignore (char c);
};

constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string help = "help";
const string Exit = "exit";
const string showval = "show";

#endif // TOKEN_STREAM_H
