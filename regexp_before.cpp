#include <string>

#include "regexp_before.h"

using namespace std;

void RegExpBefore::executeOne(const std::string& src,
                              std::vector<std::string>& dst) const
{
  vector<regmatch_t> matches;
  getMatches(src, matches, false);
  if (!matches.empty())
    {
      regmatch_t before;
      before.rm_so = 0;
      before.rm_eo = matches[0].rm_so;
      dst.push_back(extract(src, before));
    }
}
