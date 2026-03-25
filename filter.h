#ifndef _MATCHER_FILTER_H
#define _MATCHER_FILTER_H

#include <ostream>
#include <string>
#include <vector>

class Filter
{
public:
  Filter(const std::string& namep): name(namep) {}
  virtual ~Filter() {}

  // simple output for logging or debugging
  virtual void print(std::ostream& os)
  {
    os << name << std::endl;
  }

  // apply filter to one string and store result in dst
  virtual void execute(const std::string& src,
                       std::string& dst) const = 0;

protected:
  std::string expandCharSet(const std::string& pattern);

  std::string name;
};

#endif
