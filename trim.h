#ifndef _REM_TRIM_H
#define _REM_TRIM_H

#include <string>

#include "filter.h"

class Trim: public Filter
{
  // remove the characters from >pattern< from front and back
  // character defaults to ' '
public:
  Trim(const std::string& patternp): Filter("t:" + patternp), pattern(patternp)
  {
    if (pattern.empty())
      pattern = " ";
    pattern = expandCharSet(pattern);
    name = "t:" + pattern;
  }
  virtual ~Trim() {}

  virtual void executeOne(const std::string& src,
                          std::vector<std::string>& dst) const;

private:
  std::string pattern;
};
#endif
