#ifndef _MATCHER_REGEXP_H
#define _MATCHER_REGEXP_H
#include <string>
#include <vector>

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

  virtual ~RegExp() {}

protected:
  std::string pattern;
  int cflags;
  mutable RESplitter re;
};

class RegExpAfter: public RegExp
{
public:
  RegExpAfter(const std::string& pattern, int cflagsp):
    RegExp('a', pattern, cflagsp) {}

  virtual ~RegExpAfter() {}

  virtual void execute(const std::string& src,
                       std::string& dst) const
  {
    dst = "";
    if (re.setSource(src))
      dst = re.after();
  }

};

class RegExpBefore: public RegExp
{
public:
  RegExpBefore(const std::string& pattern, int cflagsp):
    RegExp('b', pattern, cflagsp) {}

  virtual ~RegExpBefore() {}

  virtual void execute(const std::string& src,
                       std::string& dst) const
  {
    dst = "";
    if (re.setSource(src))
      dst = re.before();
  }

};

class RegExpExclude: public RegExp
{
public:
  RegExpExclude(const std::string& pattern, int cflagsp):
    RegExp('x', pattern, cflagsp) {}

  virtual ~RegExpExclude() {}

  virtual void execute(const std::string& src,
                       std::string& dst) const
  {
    dst = "";
    if (!re.setSource(src))
      {
        dst = src;
      }
  }

};

class RegExpMatch: public RegExp
{
public:
  RegExpMatch(const std::string& pattern, int cflagsp):
    RegExp('m', pattern, cflagsp) {}

  virtual void execute(const std::string& src, std::string& dst) const
  {
    dst = "";
    if (re.setSource(src))
      dst = re.match();
  }

  virtual ~RegExpMatch()
  {
  }

};

class RegExpMatchMulti: public RegExp
{
public:
  RegExpMatchMulti(const std::string& pattern, int cflagsp, const std::string& del):
    RegExp('M', pattern, cflagsp), del(del) {}

  virtual void execute(const std::string& src, std::string& dst) const
  {
    std::string source = src;
    dst = "";
    while (re.setSource(source))
      {
        std::string s = re.match();
        if (s.empty())
          break;
        if (!dst.empty())
          dst += del;
        dst += re.match();
        source = re.after(); // weitersuchen
      }
  }

  virtual ~RegExpMatchMulti()
  {
  }

private:
  std::string del;

};
#endif
