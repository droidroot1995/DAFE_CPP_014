#ifndef TOKEN_STREAM_H_INCLUDED
#define TOKEN_STREAM_H_INCLUDED

#include"Token.h"

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string help = "help";
const string Exit = "exit";
const string showval = "show";

class Token_stream
{
  bool full{ false };
  Token buffer{ '\0' };

public:
  Token_stream () { }

  Token get ();
  void putback (Token t);

  void ignore (char c);
};

#endif // TOKEN_STREAM_H_INCLUDED
