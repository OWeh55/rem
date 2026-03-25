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
                       std::string& dst) const
  {
    std::string newstring;
    for (unsigned int i = 0; i < src.size(); ++i)
      {
        bool ok = pattern.find(src[i]) != std::string::npos;
        if (inverse)
          ok = !ok;
        if (ok)
          newstring += src[i];
      }
    dst = newstring;
  }

private:
  std::string pattern;
  bool inverse;
};
#endif
