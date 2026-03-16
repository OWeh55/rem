#ifndef _REM_CHARFILTER_H
#define _REM_CHARFILTER_H

#include <string>

#include "filter.h"

class CharFilter: public Filter
{
public:
  CharFilter(const std::string& patternp, bool inverse):
    Filter("c:" + patternp), pattern(patternp), inverse(inverse)
  {
    if (pattern.empty())
      throw "CharFilter: empty charset";
    pattern = expandCharSet(pattern);
    name = "c:" + pattern;
  }
  virtual ~CharFilter() {}

  virtual void execute(const std::string& src,
                       std::string& dst) const;

private:
  std::string pattern;
  bool inverse;
};
#endif
