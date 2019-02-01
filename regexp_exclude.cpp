#include <string>

#include "regexp_exclude.h"

using namespace std;

void RegExpExclude::executeOne(const std::string& src,
                               std::vector<std::string>& dst) const
{
  vector<regmatch_t> matches;
  getMatches(src, matches, false);
  if (matches.empty()) // if no match
    {
      dst.push_back(src);
    }
}
