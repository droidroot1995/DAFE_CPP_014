#include "funcs.h"

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
  case name:{
    Token following = ts.get();
    if (following.kind == '='){
        double d = expression();
        s_table.set_value(t.name, d);
        return d;
    }
    else{
    ts.putback(following);
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

double declaration (Token let_or_const)
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
  if (let_or_const.kind == let)
    return s_table.define_name (var, expression(), false);
  else
    return s_table.define_name (var, expression(), true);
}

double statement ()
{
  Token t = ts.get();
  switch (t.kind)
  {
  case let:
  case 'C':
    return declaration(t);
  default:
    ts.putback(t);
    return expression();
  }
}

void clean_up_mess ()
{
  ts.ignore (print);
}

void printHelp(){
    cout << "Zdes mozhet byt vasha reklama :)" << endl;
}

void calculate ()
{
  s_table.define_name ("pi", 3.141592653589793, true);
  s_table.define_name ("e",  2.718281828459045, true);
  while (cin)
  try
  {
    cout << prompt;
    Token t = ts.get();
    while (t.kind == print)
      t = ts.get();
    if (t.kind == quit) return;
    if (t.kind == help[0]) {printHelp(); continue;};
    if (t.kind == showval[0]) {s_table.print_values(); continue;}
    ts.putback(t);
    cout << result << statement() << endl;
  }
  catch (runtime_error& e)
  {
    cerr << e.what() << endl;
    clean_up_mess();
  }
}
