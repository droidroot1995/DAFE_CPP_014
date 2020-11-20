#include "std_lib_facilities.h"
#include "token.h"


void Token_stream::putback (Token t) //считывает всё и вводит в буфер
{
    if (full)
        error("putback() into a full buffer");
    else
    {
        buffer = t;
        full = true;
    }
}
Token Token_stream::get ()
{
    if (full)
    {
        full = false;
        return buffer;
    }

    char ch;
    do {cin.get(ch);}
    while (isspace(ch)&& ch != '\n');

    if (!cin)
        error("End of input stream"); // если больше не вводится, значит песня кончилась

    switch (ch)
    {
        case '(':
        case ')':
        case '|':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case '^':
            return Token{ ch };  //если подаётся символ, мы его возвращаем

        case enter:
        case print:
            return Token{ print }; // если подаются знаки выхода, то тут наши полномочия всё

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);
            double val;
            cin >> val;
            return Token{ number, val };  //если подётся начало числа, то возвращаем его целиком
        }

        default:
            if (isalpha(ch))
            {
                string s;
                s += ch;
                while (cin.get(ch) &&
                       (isalpha(ch) || isdigit(ch) || ch == '_'))  //читает переменные и константы
                    s += ch;
                cin.putback(ch);

                if (s == declkey) return Token{ let };
                if (s == constkey) return Token{ konst };
                if (s == helpkey) return Token{ help };
                if (s == quitkey) return Token{ quit };

                return Token{ name, s };
            }
            error("Bad token");
    }
}

void Token_stream::ignore (char c) // если вдруг введут что-то страшное
{
    if (full && c == buffer.kind)
    {
        full = false;
        return;
    }
    full = false;

    char ch = 0;
    while (cin >> ch)
        if (ch == c)
            return;
}