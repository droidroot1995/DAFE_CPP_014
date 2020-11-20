#include "calculator.cpp"

int main ()
try
{
    Symbol_table sym;

    sym.define(true, "pi", 3.141592653589793);
    sym.define(true, "e", 2.718281828459045);

    calculate(sym);
}
catch (exception& e)
{
    cerr << "exception: " << e.what() << endl;
    return 1;
}
catch (...)
{
    cerr << "Oops, unknown exception" << endl;
    return 2;
}