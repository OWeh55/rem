#include <string>

#include "regexp_after.h"

using namespace std;

void RegExpAfter::executeOne(const std::string& src,
                             std::vector<std::string>& dst) const
{
  vector<regmatch_t> matches;
  getMatches(src, matches, false);
  if (!matches.empty())
    {
      regmatch_t after;
      after.rm_so = matches[0].rm_eo;
      after.rm_eo = src.size();
      dst.push_back(extract(src, after));
    }
  else
    throw "after: no match for regexp " + pattern;
}
