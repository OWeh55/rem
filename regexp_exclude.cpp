#include <string>

#include "regexp_exclude.h"

using namespace std;

void RegExpExclude::execute(const std::string& src,
                            std::string& dst) const
{
  dst = "";
  if (!re.setSource(src))
    {
      dst = src;
    }
}
