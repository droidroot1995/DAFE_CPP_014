#include "functions.h"

Symbol_table s_table;

Token_stream ts;

double primary ()
{
    Token t = ts.get();

    switch (t.kind)
    {
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')')
            error("')' expected");
        return d;
    }

    case '-':
        return -primary();
    case '+':
        return +primary();

    case number:
        return t.value;

    case name: {
        Token tkn = ts.get();
        if (tkn.kind == '='){
            double d = expression();
            s_table.set_value(t.name, d);
            return d;
        }
        else{
            ts.putback(tkn);
            return s_table.get_value(t.name);
        }
    }
    default:
        error("primary expected");
    }
}


double term ()
{
    double left = primary();
    while (true)
    {
        Token t = ts.get();
        switch (t.kind)
        {
        case '*':
            left *= primary();
            break;

        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            break;
        }

        case '%':
        {
            int il = narrow_cast<int> (left) ;
            int i2 = narrow_cast<int> (primary());
            if (i2 == 0) error("% : divide by zero");
            left = il % i2;
            // t = ts.get();
            break;
        }

        default:
            ts.putback(t);
            return left;
        }
    }
}


double expression ()
{
    double left = term();
    while (true)
    {
        Token t = ts.get();

        switch (t.kind)
        {
        case '+':
            left += term();
            break;

        case '-':
            left -= term();
            break;

        default:
            ts.putback(t);
            return left;
        }
    }
}


double declaration (char kind)
{
    Token t = ts.get();

    if (t.kind != name)
        error("name expected in declaration");

    string var = t.name;
    if (s_table.is_declared(var))
        error(var, " declared twice");

    t = ts.get();
    if (t.kind != '=')
        error("'=' missing in declaration of ", var);

    return s_table.define_name (var, expression(), t.name == "e" ||
                                t.name == "pi" ||
                                kind == const_variable ? true:false);

}


double statement ()
{
    Token t = ts.get();
    switch (t.kind)
    {
    case let:
    case const_variable:
        return declaration(t.kind);
    default:
        ts.putback(t);
        return expression();
    }
}


void ConstDeclaration()
{
    s_table.define_name("pi", 3.141592653589793, true);
    s_table.define_name("e",  2.718281828459045, true);
}


void clean_up_mess ()
{
    ts.ignore (print);
}


void ShowHelpMessage()
{
    cout << "help - help \n const pi,e; \n quit - quit" << endl;
}


void calculate ()
{
    while (cin)
        try
    {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print)
            t = ts.get(); //Discarding output commands
        if (t.kind == quit) return;
        if (t.kind == help) ShowHelpMessage();

        ts.putback(t);
        cout << result << statement() << endl;
    }
    catch (runtime_error& e)
    {
        cerr << e.what() << endl;
        clean_up_mess();
    }
}
