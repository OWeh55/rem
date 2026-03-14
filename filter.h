#ifndef _MATCHER_FILTER_H
#define _MATCHER_FILTER_H

#include <ostream>
#include <string>
#include <vector>

class Filter
{
public:
  Filter(const std::string& namep): name(namep) {}
  virtual ~Filter()
  {
  }

  virtual void print(std::ostream& os)
  {
    os << name << std::endl;
  }

  // apply filter to one string and append result to dst
  virtual void executeOne(const std::string& src,
                          std::vector<std::string>& dst) const = 0;

  // apply filter to vector of string generating new dst
  virtual void execute(const std::vector<std::string>& src,
                       std::vector<std::string>& dst) const
  {
    if (&src == &dst)
      throw "src and dst are same";
    dst.clear();
    for (unsigned int i = 0; i < src.size(); ++i)
      {
        executeOne(src[i], dst);
      }
  }

  // apply filter to string generating new dst
  virtual void execute(const std::string& src,
                       std::vector<std::string>& dst) const
  {
    dst.clear();
    executeOne(src, dst);
  }

protected:
  std::string expandCharSet(const std::string& pattern);

  std::string name;
};

#endif
