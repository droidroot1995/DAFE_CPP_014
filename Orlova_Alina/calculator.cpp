#include "token.h"
#include "variable.h"

double expression (Token_stream &ts, const Symbol_table &sym);

double primary (Token_stream &ts, const Symbol_table sym)
{
    Token t = ts.get();
    switch (t.kind)
    {
        case '(':
        {
            double d = expression(ts, sym);
            t = ts.get();
            if (t.kind != ')')
                error("'(' expected");
            return d;
        }

        case '-':
            return -primary(ts, sym);
        case '+':
            return +primary(ts, sym);

        case number:
            return t.value;

        case name:
        {
            string str = t.name;
            return sym.get(str);
        }
        default:
            error("primary expected");
    }
}


double term (Token_stream &ts, const Symbol_table &sym)
{
    double left = primary(ts, sym);
    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
            case '*':
                left *= primary(ts, sym);
                break;

            case '/':
            {
                double d = primary(ts, sym);
                if (d == 0) error("divide by zero");
                left /= d;
                break;
            }

            case '%':
            {
                double d = primary(ts, sym);
                if (d == 0) error("%: divide by zero");
                left = fmod(left, d);
                break;
            }

            case '^':
            {
                double d = primary(ts, sym);
                left = pow(left, d);
                break;
            }

            default:
                ts.putback(t);
                return left;
        }
    }
}


double expression (Token_stream &ts, const Symbol_table &sym)
{
    double left = term(ts, sym);
    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
            case '+':
                left += term(ts, sym);
                break;

            case '-':
                left -= term(ts, sym);
                break;

            default:
                ts.putback(t);
                return left;
        }
    }
}

double declaration (Token_stream &ts, Symbol_table &sym, bool is_const)
{
    Token t = ts.get();
    if (t.kind != name)
        error("name expected in declaration");

    string var = t.name;
    if (sym.is_declared(var))
        error(var, " declared twice");

    t = ts.get();
    if (t.kind != '=')
        error("'=' missing in declaration of ", var);

    return sym.define(is_const, var, expression(ts, sym));
}

double change_var(Token_stream &ts, Symbol_table &sym, string var)
{
    if (!sym.is_declared(var))
        error(var, " isn't declared yet");

    double x = expression(ts, sym);
    sym.set(var, x);
    return sym.get(var);
}

double statement (Token_stream &ts, Symbol_table &sym)
{
    Token t = ts.get();
    switch (t.kind)
    {
        case let:
            return declaration(ts, sym, false);

        case konst:
            return declaration(ts, sym, true);

        case name:
        {
            Token named = t;
            string var = t.name;
            t = ts.get();
            if (t.kind == '=')
                return change_var(ts, sym, var);
            ts.putback(named);
            ts.putback(t);
            return expression(ts, sym);
        }

        default:
            ts.putback(t);
            return expression(ts, sym);
    }
}


void clean_up_mess (Token_stream &ts)
{
    ts.ignore(enter);
}

void print_help()
{
    cout << "Hello! It is calculator, it is all my possibilities:\n";
    cout << "+ - add;\n"
            "- - subtraction;\n"
            "* - multiply;\n"
            "/ - division;\n"
            "% - remainder of division;\n"
            "^ - exponentiation;\n"
            "() - expresion with first-priority;\n";
    cout << "Here is some integrated constant:\n";
    cout << "pi = 3.141592653589793\n"
            "e = 2.718281828459045" << endl;
}

void calculate (Symbol_table &sym)
{
    Token_stream ts;
    while (cin)
        try
        {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
            {
                t = ts.get();
            }


            if (t.kind == help)
            {
                print_help();
                continue;
            }

            if (t.kind == quit) return;

            ts.putback(t);
            cout << result << statement(ts, sym) << endl;
        }
        catch (runtime_error& e)
        {
            cerr << e.what() << endl;
            clean_up_mess(ts);
        }
}