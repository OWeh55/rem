#include "regexp_match.h"

#include <iostream>

using namespace std;

void RegExpMatch::execute(const std::string& src, std::string& dst) const
{
  dst = "";
  if (re.setSource(src))
    dst = re.match();
}
