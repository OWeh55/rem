#include "regexp_match.h"

#include <iostream>

using namespace std;

RegExpMatch::RegExpMatch(const string& pattern, int cflagsp, bool all):
  RegExp('m', pattern, cflagsp, all)
{
  cflags |= REG_EXTENDED;
}

/*
void RegExpMatch::getMatches(const std::string &src, std::vector<regmatch_t> &matches, bool all) const
{
  matches.clear();
  const int maxMatchNr = 10;
  regmatch_t pmatch[maxMatchNr]; // result buffer
  regex_t preg;
  int rc = regcomp(&preg, pattern.c_str(), cflags);
  if (rc != 0)
    {
      throw string("Cannot compile ") + pattern + ": " + regexError(preg, rc);
    }
  int first = 0;
  bool done = false;
  while (!done && first < (int)src.size() &&
         regexec(&preg, src.substr(first).c_str(), 10, pmatch, 0) == 0)
    {
      if ((pmatch[0].rm_eo - pmatch[0].rm_so) == 0)
        throw string("Empty string matches ") + name;

      int results = 0; // number of results
      while (results < maxMatchNr && pmatch[results].rm_so != -1)
        results++;

      // "correct" first match
      pmatch[0].rm_so += first;
      pmatch[0].rm_eo += first;

      if (results == 1) // no substring with '()'
        {
          matches.push_back(pmatch[0]);
        }
      else
        {
          // pmatch [0] is whole match, pmatch[1]... are substrings
          // ignore whole match
          for (int i = 1; i < results; ++i)
            {
              // "correct" match
              pmatch[i].rm_so += first;
              pmatch[i].rm_eo += first;
              matches.push_back(pmatch[i]);
              //     cout << i << "- " << res << endl;
            }
        }
      first = pmatch[0].rm_eo;
      done = !all;
    }
  regfree(&preg);
}

string RegExpMatch::extract(const string &src, regmatch_t pmatch)
{
  string res;
  for (int k = pmatch.rm_so; k < pmatch.rm_eo; ++k)
    res += src[k];
  return res;
}
*/

void RegExpMatch::executeOne(const std::string& src, std::vector<std::string>& dst) const
{
  vector<regmatch_t> matches;
  getMatches(src, matches, all);
  for (unsigned int i = 0; i < matches.size(); ++i)
    dst.push_back(extract(src, matches[i]));
}
