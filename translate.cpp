#include <iostream>
#include "translate.h"

using namespace std;

void Translate::execute(const std::string& src,
                        std::string& dst) const
{
  string newstring(src);
  for (unsigned int i = 0; i < src.size(); ++i)
    {
      if (trmap.count(src[i]) > 0)
        {
          newstring[i] = trmap.at(src[i]);
        }
    }
  dst = newstring;
}
