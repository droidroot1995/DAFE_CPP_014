#include"Variable.h"

Variable::Variable (string n, double v, bool c)
    : name{ n }, value{ v }, constant{ c }
  { }

double Symbol_table::get_value (string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s)
      return var_table[i].value;

  error("get: undefined name ", s);
}

void Symbol_table::print_values(){
    for (int i = 0; i < var_table.size(); ++i){
        if (var_table[i].constant == 1)
            cout << "constant ";
        cout << var_table[i].name << " = " << var_table[i].value << "\t";
        if ((i !=0 )&&(i % 3 == 0))
            cout << endl;
    }
    cout << endl;
}

void Symbol_table::set_value (string s, double d)
{
  for (int i = 0; i <= var_table.size(); ++i)
  {
    if (var_table[i].name == s)
    {
      if (var_table[i].constant == false){
      var_table[i].value = d;
      return;
      }
      error(s, " - const");
    }
  }

  error("set: undefined name ", s);
}

bool Symbol_table::is_declared (string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s) return true;
  return false;
}

double Symbol_table::define_name (string var, double val, bool con)
{
  if (is_declared(var))
    error(var, " declared twice");

  var_table.push_back (Variable{ var, val, con });

  return val;
}

