#include "std_lib_facilities.h"

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


void Token_stream::putback (Token t)
{
    if (full)
        error("putback() into a full buffer");

    buffer = t;
    full = true;
}


constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char help = 'H';
constexpr char const_variable = 'C';

const string prompt = "> ";
const string result = "= ";
const string constkey = "const";
const string declkey = "let";
const string helpkey = "help";


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


class Variable
{
public:
    string name;
    double value;
    bool is_const;

    Variable (string n, double v, bool isconst)
        : name{ n }, value{ v }, is_const{ isconst }
    { }
};


class Symbol_table{
public:
    vector<Variable> var_table;
    double get_value (const string &s);
    void set_value (const string &s, const double &d);
    bool is_declared (const string &s);
    double define_name (const string &var, const double &val, const bool &con);
    void print_values();
};


double Symbol_table::get_value (const string &s)
{//Returns the value of a variable named s

    for (int i = 0; i < (int)var_table.size(); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    error("get: undefined name ", s);
}

void Symbol_table::set_value (const string &s, const double &d)
{
    for (int i = 0; i < (int)var_table.size(); ++i)
    {
        if (var_table[i].name == s && !var_table[i].is_const)
        {
            var_table[i].value = d;
            return;
        }
    }

    error("set: undefined name ", s);
}

bool Symbol_table::is_declared (const string &s)
{// Is s in vector var_table

    for (int i = 0; i < (int)var_table.size(); ++i)
        if (var_table[i].name == s) return true;

    return false;
}

double Symbol_table::define_name (const string &var, const double &val, const bool &is_const)
{//Append (var,val) in vecrot var_table

    if (is_declared(var))
        error(var, " declared twice");

    var_table.push_back (Variable{ var, val, is_const});

    return val;
}

Symbol_table s_table;

Token_stream ts;

double expression ();

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


int main () {
    try
    {
        s_table.define_name("pi", 3.141592653589793, true);
        s_table.define_name("e",  2.718281828459045, true);

        calculate();

        keep_window_open();
        return 0;
    }
    catch (exception& e)
    {
        cerr << "exception: " << e.what() << endl;
        keep_window_open("~~");
        return 1;
    }
    catch (...)
    {
        cerr << "Unknown exception!" << endl;
        keep_window_open("~~");
        return 2;
    }
}
