#include "token.h"

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch;
    in >> ch;

    switch (ch)
    {
    case '*':
    case '/':
    case ',':
    case '+':
    case '-':
    case '(':
    case ')':
    case '=':
    case quit:
    case print:
        return Token{ch};

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
    {
        in.putback(ch);
        double val;
        in >> val;
        return Token{number, val};
    }
    case '\000':
        return Token(quit);
    default:
        if (isalnum(ch))
        {
            string s;
            s += ch;
            while (in.get(ch) && (isalpha(ch) || isdigit(ch)))
            {
                s += ch;
            }
            in.putback(ch);

            if (s == deckey)
            {
                return Token{let, s};
            }
            if (s == powerkey)
            {
                return Token{func, powerkey};
            }
            if (s == sqrtkey)
            {
                return Token{func, sqrtkey};
            }

            return Token{name, s};
        }
        break;
    }
    error("Bad token.");
    return Token{'\0'};
}

void Token_stream::ignore(char c)
{
    if (full && buffer.kind == c||buffer.kind == quit)
    {
        full = false;
        return;
    }
    char ch;
    while (in >> ch)
        if (ch == c||buffer.kind == quit)
            return;
}

void Token_stream::put_back(Token tk)
{
    if (full){
        error("The buffer is full.");
    }

    full = true;
    buffer = tk;
    
}