#pragma once
#include <Token.h>

const string prompt = "> ";
const string result = "= ";
const string constkey = "const";
const string declkey = "let";
const string helpkey = "help";

class Token_stream
{
public:
    Token_stream () { }

    Token get ();
    void putback (Token t);

    void ignore (char c);

private:
    bool full{ false };
    Token buffer{ '\0' };
};
