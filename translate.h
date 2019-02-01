#ifndef _REM_TRANSLATE_H
#define _REM_TRANSLATE_H

#include <map>

#include <string>

#include "filter.h"

class Translate: public Filter
{
  // "translate" char[s] to other char[s]
  // parameter is a string with pairs of chars
  // each pair (old char, new char) describes one translation
public:
  Translate(const std::string& patternp): Filter("T:" + patternp)
  {
    if ((patternp.size() % 2) != 0)
      throw std::string("Wrong translation list ") + patternp;
    for (unsigned int i = 0; i < patternp.size(); i += 2)
      {
        trmap[patternp[i]] = patternp[i + 1];
      }
  }

  virtual ~Translate() {}

  virtual void executeOne(const std::string& src,
                          std::vector<std::string>& dst) const;

private:
  std::map<char, char> trmap;
};
#endif
