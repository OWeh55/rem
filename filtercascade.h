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
                       std::string& dst) const
  {
    std::string src = srcstring;

    for (unsigned int i = 0; i < filters.size(); ++i)
      {
#ifdef DEBUG
        filters[i]->print(std::cout);
        std::cout << std::endl;
        std::cout << "in:" << src << std::endl;
#endif
        filters[i]->execute(src, dst);
#ifdef DEBUG
        std::cout << "out:" << dst << std::endl;
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
