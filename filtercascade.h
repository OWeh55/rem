#ifndef _MATCHER_FILTERCASCADE_H
#define _MATCHER_FILTERCASCADE_H

#include <vector>

#include "filter.h"

class FilterCascade
{
public:
  virtual ~FilterCascade()
  {
    for (unsigned int i = 0; i < filters.size(); ++i)
      delete filters[i];
  }

  virtual void execute(const std::string& srcstring,
                       std::vector<std::string>& dst) const
  {
    std::vector<std::string> src;
    src.push_back(srcstring);
    for (unsigned int i = 0; i < filters.size(); ++i)
      {
#ifdef DEBUG
        filters[i]->print(std::cout);
        std::cout << std::endl;
        for (unsigned int k = 0; k < src.size(); ++k)
          std::cout << "in:" << src[k] << std::endl;
#endif
        filters[i]->execute(src, dst);
#ifdef DEBUG
        for (unsigned int k = 0; k < dst.size(); ++k)
          std::cout << "out:" << dst[k] << std::endl;
#endif
        src = dst;
      }
  }

  virtual void append(Filter* f)
  {
    filters.push_back(f);
  }

  virtual void print(std::ostream& os) const
  {
    for (auto x : filters)
      x->print(os);
  }
protected:
  std::vector<Filter*> filters;
};

#endif
