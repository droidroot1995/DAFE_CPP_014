#ifndef TOKEN_H
#define TOKEN_H

#include "std_lib_facilities.h"

constexpr char let = 'L';
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char func = 'f';
constexpr char name = 'a';

const string sqrtkey = "sqrt";
const string powerkey = "pow";
const string deckey = "let";
const string result = "= ";
const string prompt = "> ";

struct Token
{
    string name;
    char kind;
    double value;

    Token(char ch)
        : kind{ch}, value{0} {}

    Token(char ch, double val)
        : kind{ch}, value{val} {}

    Token(char ch, string name)
        : kind(ch), name{name} {}
};

class Token_stream
{
private:
    bool full{false};
    Token buffer{'\0'};
    istream &in;
    

public:

    Token_stream()
        : in{cin} {}

    Token_stream(istream &s)
        : in{s} {}

    Token get();
    void ignore(char c);
    void put_back(Token tk);
};
#endif