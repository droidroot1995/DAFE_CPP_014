#include <Token.h>
#include <Token_stream.h>
#include <Variable.h>
#include <functions.h>


int main () {
    try
    {
        ConstDeclaration();
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
