#include <Token_stream.h>

void Token_stream::putback (Token t)
{
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}


Token Token_stream::get ()
{//Token create
    if (full)
    { //Checking if Token in the buffer

        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch (ch)
    {
    case quit:
    case help:
    case print:
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
        return Token{ ch };

    case '\n':
        return Token { print };

    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch); //Returning a digit to the input stream
        double val;
        cin >> val; //Reading a floating-point number
        return Token{ number, val };
    }

    default:
        if (isalpha(ch))
        {
            string s;
            s += ch;
            while (cin.get(ch) &&
                   (isalpha(ch) || isdigit(ch) || ch == '_'))
                s += ch;
            cin.putback(ch);

            if (s == declkey) return Token{ let };
            if (s == constkey) return Token { const_variable };
            if (s == helpkey) return Token { help };

            return Token{ name, s };
        }
        error("Bad token");
    }
}


void Token_stream::ignore (char c)
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    char ch; //getchar?
    while (cin >> ch)
        if (ch == c) return;
}
