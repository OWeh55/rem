#include "regexp_match.h"

#include <iostream>

using namespace std;

void RegExpMatch::execute(const std::string& src, std::string& dst) const
{
  dst = "";
  if (re.setSource(src))
    dst = re.match();
}

void RegExpMatchMulti::execute(const std::string& src, std::string& dst) const
{
  std::string source = src;
  dst = "";
  while (re.setSource(source))
    {
      if (!dst.empty())
        dst += del;
      dst += re.match();
      source = re.after(); // weitersuchen
    }
}
