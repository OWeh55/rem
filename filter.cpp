#include "filter.h"

#include <iostream>

using namespace std;

std::string Filter::expandCharSet(const std::string& p, bool withNewLine)
{
  // we "compile" pattern. pattern may describe chars by
  // - char itself
  // - char as escape sequence '\t', '\n'
  // - charsets with [a-b]
  // - special charsets with [[digits]]
  int pos = 0;
  int size = p.size();
  int last = size - 1;
  string result;
  while (pos < size)
    {
      char c = p[pos];
      switch (c)
        {
        case '\\': // escape sequences
        {
          if (pos == last) // as last char backslash respresents itself
            {
              result += '\\';
              pos++;
            }
          else
            {
              char c2 = p[pos + 1];
              switch (c2)
                {
                case 't':
                  result += '\t';
                  break;
                case '\'':
                  result += '\'';
                  break;
                case '\"':
                  result += '\"';
                  break;
                case '\\':
                  result += '\\';
                  break;
                case 'n':
                {
                  if (withNewLine)
                    result += '\n';
                  else
                    throw "newline not allowed in charset";
                }
                break;
                default:
                  result += c2;
                }
              pos += 2;
            }
        }
        break;
        case '[':
        {
          pos++;
          if (pos >= size) // as last char [ represents itself
            result += '[';
          else
            {
              char c1 = p[pos];
              pos++;
              if (pos >= size || p[pos] != '-')
                throw "- in charset expected";
              pos++;
              if (pos >= size)
                throw "second char in charset expected";
              char c2 = p[pos];
              pos++;
              if (pos >= size || p[pos] != ']')
                throw "] in charset expected";
              pos++;
              if (c1 > c2)
                std::swap(c1, c2);
              for (char cc = c1; cc <= c2; cc++)
                result += cc;
            }
        }
        }
    }
  return result;
}
