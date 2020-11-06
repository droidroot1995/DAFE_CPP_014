#pragma once
#include <std_lib_facilities.h>

constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char help = 'H';
constexpr char const_variable = 'C';

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
    Token (char ch , string n)
        : kind{ch} , name{n}
    { }
};
