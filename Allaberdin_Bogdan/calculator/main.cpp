#include"functions.h"

int main (){
try
{
  calculate();
  keep_window_open();
  return 0;
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
}
