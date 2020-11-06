#include <Variable.h>

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
