#ifndef _MATCHER_REGEXP_H
#define _MATCHER_REGEXP_H
#include <string>
#include <vector>

#include <sys/types.h>
#include <regex.h>

#include "filter.h"

class RegExp: public Filter
{
public:
  //  RegExp(const std::string &pattern, int cflagsp, bool all = false);
  RegExp(char m, const std::string& pattern, int cflagsp, bool all = false);

  virtual void executeOne(const std::string& src, std::vector<std::string>& dst) const = 0;

  virtual ~RegExp()
  {
    //    regfree(&preg);
  }

protected:
  virtual void getMatches(const std::string& src,
                          std::vector<regmatch_t>& matches, bool all) const;

  static std::string extract(const std::string& src, regmatch_t pmatch);

  static std::string regexError(const regex_t& preg, int rc)
  {
    char errorBuffer[5000];
    regerror(rc, &preg, errorBuffer, 5000);
    return errorBuffer;
  }

  std::string pattern;
  int cflags;
  bool all;
};
#endif
