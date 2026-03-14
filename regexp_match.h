#ifndef _MATCHER_REGEXPMATCH_H
#define _MATCHER_REGEXPMATCH_H

#include <string>
#include <vector>

#include <sys/types.h>
#include <regex.h>

#include "regexp.h"

class RegExpMatch: public RegExp
{
public:
  RegExpMatch(const std::string& pattern, int cflagsp):
    RegExp('m', pattern, cflagsp) {}

  virtual void execute(const std::string& src, std::string& dst) const;

  virtual ~RegExpMatch()
  {
  }

};
#endif
