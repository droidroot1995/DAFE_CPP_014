#include "std_lib_facilities.h"
#include "variable.h"


double Symbol_table::get (string s) const
{
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    error("get_value: undefined name ", s);
}

void Symbol_table::set (string s, double d)
{
    for (int i = 0; i < var_table.size(); ++i)
    {
        if (var_table[i].name == s)
        {
            var_table[i].value = d;
            return;
        }
    }

    error("set: undefined name ", s);
}

bool Symbol_table::is_declared (string s) const
{
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s) return true;
    return false;
}

double Symbol_table::define(bool is_const, string var, double val)
{
    if (is_declared(var))
        error(var, " declared twice");

    if (is_const)
        error(var, " can't change consts");

    var_table.push_back (Variable{ is_const, var, val });

    return val;
}

