#ifndef _MATCHER_REGEXP_BEFORE_H
#define _MATCHER_REGEXP_BEFORE_H

#include "regexp.h"

class RegExpBefore: public RegExp
{
public:
  RegExpBefore(const std::string& pattern, int cflagsp):
    RegExp('b', pattern, cflagsp) {}

  virtual ~RegExpBefore() {}
  
  virtual void execute(const std::string& src,
                       std::string& dst) const  
  {
    dst = "";
    if (re.setSource(src))
      dst = re.before();
  }

};

#endif
