#include "variable.h"

double Table_variables::define_variable(string variable_name, double variable_value)
{
    if (is_defined(variable_name))
    {
        error(variable_name,"declared twice.");
    }
    variables.push_back({Variable{variable_name, variable_value}});
    return variable_value;
}

double Table_variables::get_value(string variable_name)
{
    for (auto &&i : variables)
    {
        if (i.name == variable_name)
            return i.value;
    }
    error("get: the label of the variable did't find.");
    return 0;
}

void Table_variables::set_value(string variable_name, double new_value)
{
    for (auto &&i : variables)
    {
        if (i.name == variable_name)
            i.value = new_value;
        return;
    }
    error("set: the label of the variable did't find.");
}

bool Table_variables::is_defined(string variable_name)
{
    for (auto &&i : variables)
    {
        if (i.name == variable_name)
            return true;
    }
    return false;
}
