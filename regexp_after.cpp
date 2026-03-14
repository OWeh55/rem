#include <string>

#include "regexp_after.h"

using namespace std;

void RegExpAfter::execute(const std::string& src,
                          std::string& dst) const
{
  dst = "";
  if (re.setSource(src))
    dst = re.after();
}
