#include "calculator.h"
#include "cmath"

double Calculator::primary()
{
    Token tk{'\0'};
    tk = ts.get();
    switch (tk.kind)
    {
    case '(':
    {
        double val = expression();
        tk = ts.get();
        if (tk.kind != ')')
        {
            error("primary exeption.");
            ts.put_back(tk);
        }
        return val;
    }
    case '+':

        return +primary();

    case '-':

        return -primary();

    case func:
    {
        Token tk2 = ts.get();
        if (tk2.kind != '(')
            error("invaled declaration");

        if (tk.name == sqrtkey)
        {

            ts.put_back(tk2);
            double val = primary();
            if (val < 0)
                error("sqrt: square root of negative number");
            return sqrt(val);
        } 
    }
    case number:

        return tk.value;

    case name:

        return variables.get_value(tk.name);

    default:

        error("primary error");
        return 0;
    }
}
double Calculator::expression()
{
    double left = term();
    Token tk{'\0'};
    while (true)
    {
        tk = ts.get();
        switch (tk.kind)
        {
        case '+':
            left += term();
            break;
        case '-':
            left -= term();
            break;

        default:
            ts.put_back(tk);
            return left;
        }
    }
}
double Calculator::term()
{
    double left = primary();
    Token tk{'\0'};
    while (true)
    {
        tk = ts.get();
        switch (tk.kind)
        {

        case '*':
            left *= primary();
            break;
        case '/':
        {
            double val = primary();
            if (val == 0)
            {
                error("divide by zero.");
                left = 0;
                break;
            }
            left /= val;
            break;
        }
        default:
            ts.put_back(tk);
            return left;
        }
    }
}
double Calculator::declaration()
{
    Token tk = ts.get();
    if (tk.kind != name)
        error("declaration, token name expected.");

    string var = tk.name;
    if (variables.is_defined(var))
        error(var, " declared twice");
    tk = ts.get();
    if (tk.kind != '=')
        error("'=' expected in declaration");
    return variables.define_variable(var, expression());
}

double Calculator::statement()
{
    Token tk = ts.get();
    switch (tk.kind)
    {
    case let:
        return declaration();

    default:
        ts.put_back(tk);
        return expression();
    }
}

void Calculator::clear_up_mess()
{
    ts.ignore(print);
}

void Calculator::execute()
{
    variables.define_variable("pi", 3.14159265);
    variables.define_variable("e", 2.71);

    while (true)
    {
        try
        {
            os << prompt;
            Token tk = ts.get();
            while (tk.kind == print)
                tk = ts.get();
            if (tk.kind == quit)
                return;
            ts.put_back(tk);
            double val = statement();
            os << result << val << endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            clear_up_mess();
        }
    }
}
