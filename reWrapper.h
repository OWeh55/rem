#ifndef REWRAPPER
#define REWRAPPER

#include <string>

#include <sys/types.h>
#include <regex.h>

// vereinfachter C++-wrapper für reguläre ausdrücke
// ein re, ein treffer
// resultate: davor, treffer, danach
class REWrapper
{
  const int maxMatchNr=10;
  
public:
  REWrapper(const std::string& pattern, int cflags):
    pattern(pattern), cflags(cflags | REG_EXTENDED), re_stat(-1)
  {
  };

  bool setSource(const std::string& sstr)
  {
    source = sstr;
    int re_stat = regcomp(&preg, pattern.c_str(), cflags);
    if (re_stat != 0)
      throw std::string("cannot compile ") + pattern;

    regmatch_t pmatch[maxMatchNr];
    int rc = regexec(&preg, source.c_str(), maxMatchNr, pmatch, 0);
    if (rc == 0) // Erfolg
      {
        ss = pmatch[0].rm_so;
        se = pmatch[0].rm_eo;
        return true;
      }
    return false;
  }
  
  std::string before() const
  {
    return source.substr(0, ss);
  }

  std::string match() const
  {
    return source.substr(ss, se - ss);
  }

  std::string after() const
  {
    return source.substr(se);
  }

private:
  std::string pattern;
  int cflags;
  std::string source;
  int re_stat;
  regex_t preg;
  regoff_t ss;
  regoff_t se;

};

#endif
