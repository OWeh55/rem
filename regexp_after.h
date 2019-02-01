#ifndef _MATCHER_REGEXP_AFTER_H
#define _MATCHER_REGEXP_AFTER_H

#include "regexp.h"

class RegExpAfter: public RegExp
{
public:
  RegExpAfter(const std::string& pattern, int cflagsp):
    RegExp('a', pattern, cflagsp) {}

  virtual ~RegExpAfter() {}

  virtual void executeOne(const std::string& src,
                          std::vector<std::string>& dst) const;
};

#endif
