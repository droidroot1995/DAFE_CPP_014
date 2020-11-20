//
// This is example code from Chapter 6.7 "Trying the second version" of
// "Software - Principles and Practice using C++" by Bjarne Stroustrup
//

/*
  This file is known as calculator02buggy.cpp

  I have inserted 5 errors that should cause this not to compile
  I have inserted 3 logic errors that should cause the program to give wrong results

  First try to find and remove the bugs without looking in the book.
  If that gets tedious, compare the code to that in the book (or posted source code)

  Happy hunting!

*/

#include "hehe.h"

const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";

class Token
{
public:
  char kind;        /// what kind of token
  double value;     /// for numbers: a value

  Token (char ch)
    : kind{ ch }, value{ 0 }  { }

  Token (char ch, double val)
    : kind{ ch }, value{ val }  { }
};


class Token_stream
{
public:
  Token_stream ();    /// make a Token_stream that reads from cin
  Token get ();
  void putback(Token t);
  void ignore(char c);

private:
  bool full {false};  /// is there a Token in the buffer?
  Token buffer;        /// here we keep a Token put back using putback()
};


Token_stream::Token_stream ()
  : buffer{ 0 }        /// no Token in buffer
{
}

void Token_stream::ignore(char c)
{
    if (full && c==buffer.kind){
        full = false;
        return;
    }
    full = false;
    char ch = 0;
    while (cin>>ch)
        if (ch==c) return;
}

void Token_stream::putback (Token t)
{
  if (full)
    error("putback() into a full buffer");

  buffer = t;
  full = true;
}


Token Token_stream::get ()
{
  if (full)         // do we already have a Token ready?
  {
    full = false;   // remove Token from buffer
    return buffer;
  }

  char ch;
  cin >> ch;  // note that >> skips whitespace (space, newline, tab, ...)

  switch (ch)
  {
  case print:    // for "print"
  case quit:    // for "quit"
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
    return Token{ ch };      // let each character represent itself
  case '.':

  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  {
    cin.putback(ch);         // put digit back into the input stream
    double val;
    cin >> val;              // read a floating-point number
    return Token{number, val};  // let '8' represent "a number"
  }

  default:
    error("Bad token");
  }
}



Token_stream ts;

double expression ();


/// deal with numbers and parentheses
double primary ()
{
  Token t = ts.get();
  switch (t.kind)
  {
  case '(':          // handle '(' expression ')'
  {
    double d = expression();
    t = ts.get();
    if (t.kind != ')')
      error("')' expected");
    return d;
  }

  case number:          // we use '8' to represent a number
    return t.value;

  case '-':
      return - primary();

  case '+':
      return primary();

  default:
    error("primary expected");
  }
}


/// deal with *, /, and %
double term ()
{
  double left = primary();
  Token t = ts.get();    // get the next token from token stream

  while (true)
  {
    switch (t.kind)
    {
    case '*':
      left *= primary();
      t = ts.get();
      break;

    case '%':
    {
      double d = primary();
      if (d == 0) error("divide by zero");
      left = fmod(left,d);
      t = ts.get();
      break;
    }

    case '/':
    {
      double d = primary();
      if (d == 0) error("divide by zero");
      left /= d;
      t = ts.get();
      break;
    }

    default:
      ts.putback(t);     // put t back into the token stream
      return left;
    }
  }
}


/// deal with + and -
double expression ()
{
  double left = term();  // read and evaluate a Term
  Token t = ts.get();    // get the next token from token stream

  while (true)
  {
    switch (t.kind)
    {
    case '+':
      left += term();    // evaluate Term and add
      t = ts.get();
      break;

    case '-':
      left -= term();    // evaluate Term and subtract
      t = ts.get();
      break;

    default:
      ts.putback(t);     // put t back into the token stream
      return left;       // finally: no more + or -: return the answer
    }
  }
}

void clean_up_mess()
{
    ts.ignore(print);
}

void calculate()
{
    while (cin)
    try {
      cout << prompt;
      Token t = ts.get();
      while (t.kind == print) t = ts.get();  // 'q' for quit
      if (t.kind == quit) return;       // ';' for "print now"
      ts.putback(t);
      cout << result << expression() << '\n';
     }
    catch (exception& e){
        cerr << e.what() << '\n';
        clean_up_mess();
    }
}

int main ()
try{
  cout << "Welcome to calculator-programme!" << endl;
  cout << "'q' - quit, ';' - output the result" << endl;
  calculate();
  keep_window_open();
  return 0;
}
catch (runtime_error& e)
{
  cerr <<"error: "<< e.what() <<'\n';
  keep_window_open("~~");
  return 1;
}
catch (...)
{
  cerr <<"Oops: unknown exception!\n";
  keep_window_open("~~");
  return 2;
}

