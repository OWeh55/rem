#include <iostream>
#include "trim.h"

using namespace std;

void Trim::executeOne(const std::string& src, std::vector<std::string>& dst) const
{
  string newstring;
  int first = -1;
  for (unsigned int i = 0; first < 0 && i < src.size(); ++i)
    {
      if (pattern.find(src[i]) == string::npos)
        {
          first = i;
        }
    }

  if (first >= 0)
    {
      int last = -1;
      for (int i = src.size() - 1; last < 0 && i >= 0; --i)
        {
          if (pattern.find(src[i]) == string::npos)
            last = i;
        }
      if (last >= 0)
        newstring = src.substr(first, last - first + 1);
    }
  dst.push_back(newstring);
}
