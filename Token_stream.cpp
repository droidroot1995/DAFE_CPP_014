#include "Token_stream.h"

void Token_stream::putback (Token t)
{
  if (full)
    error("putback() into a full buffer");
  buffer = t;
  full = true;
}

Token Token_stream::get ()
{
  if (full)
  {
    full = false;
    return buffer;
  }
  char ch;
  ch = getchar();
  while (ch == ' ')
    ch = getchar();
  switch (ch)
  {
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
    return Token{ print };
  case '.':
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
  {
    cin.putback(ch);
    double val;
    cin >> val;
    return Token{ number, val };
  }
  default:
    if (isalpha(ch))
    {
      string s;
      s += ch;
      while (cin.get(ch) && (isalpha(ch) || isdigit(ch)|| ch =='_'))
        s += ch;
      cin.putback(ch);
      if (s == declkey) return Token{ let };
      if (s == "con") return Token{ 'C' };
      if (s == Exit) return Token{ quit };
      if (s == help) return Token{ help[0] };
      if (s == showval) return Token{showval[0]};
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
  char ch = getchar();
  while (ch)
  {
    if (ch == '\n')
        ch = c;
    if (ch == c)
        return;
    ch = getchar();
  }
}
