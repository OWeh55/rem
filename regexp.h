#ifndef _MATCHER_REGEXP_H
#define _MATCHER_REGEXP_H
#include <string>
#include <vector>

#include <sys/types.h>
#include "RESplitter.h"

#include "filter.h"

class RegExp: public Filter
{
public:
  RegExp(char m, const std::string& pattern, int cflagsp):
    Filter(std::string(1, m) + ':' + pattern),
    pattern(pattern), cflags(cflagsp),
    re(pattern, cflags | REG_EXTENDED)
  {
  }

  virtual void execute(const std::string& src, std::string& dst) const = 0;

  virtual ~RegExp()
  {
  }

protected:
  std::string pattern;
  int cflags;
  mutable RESplitter re;
};

#endif
