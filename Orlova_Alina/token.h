#ifndef CALCULATOR_ORL_TOKEN_H
#define CALCULATOR_ORL_TOKEN_H
#include "std_lib_facilities.h"

constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char help = 'h';
constexpr char konst = 'k';
constexpr char enter = '\n';

const string prompt = "> ";
const string result = "= ";
const string declkey = "let";
const string constkey = "const";
const string helpkey = "help";
const string quitkey = "quit";

struct Token      //структура для данных
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

    Token (char ch, string s)
            : kind{ ch }, name{ move(s) }
    { }
};

class Token_stream        // класс, определяющий возможные действия с переменными
{
    bool full{ false };
    Token buffer{ '\0' };

public:
    Token_stream (): in {cin} { }
    Token_stream (istream& s): in {s} { }

    Token get ();
    void putback (Token t);

    void ignore (char c);
    operator bool() const;

private:
    istream& in;
};

#endif //CALCULATOR_ORL_TOKEN_H
