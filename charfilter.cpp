#include <iostream>
#include "charfilter.h"

void CharFilter::execute(const std::string& src, std::string& dst) const
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
