#include <string>

#include "regexp_before.h"

using namespace std;

void RegExpBefore::execute(const std::string& src,
                           std::string& dst) const
{
  dst = "";
  if (re.setSource(src))
    dst = re.before();
}
