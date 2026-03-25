#ifndef _MATCHER_REGEXP_EXCLUDE_H
#define _MATCHER_REGEXP_EXCLUDE_H

#include "regexp.h"

class RegExpExclude: public RegExp
{
public:
  RegExpExclude(const std::string& pattern, int cflagsp):
    RegExp('x', pattern, cflagsp) {}

  virtual ~RegExpExclude() {}

  virtual void execute(const std::string& src,
                       std::string& dst) const
  {
    dst = "";
    if (!re.setSource(src))
      {
	dst = src;
      }
  }
  
};

#endif
