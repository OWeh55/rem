#ifndef RESPLITTER_H
#define RESPLITTER_H

#include <stdexcept>
#include <string>

#include <sys/types.h>
#include <regex.h>

/**
 * C++-Wrapper fuer POSIX Extended Regular Expressions.
 *
 * Ein Muster, ein Treffer. Ergebnis: before() / match() / after().
 *
 * Beispiel:
 *   RESplitter re("[[:digit:]]+");
 *   if (re.setSource("Preis: 42 Euro"))
 *       std::cout << re.match();  // "42"
 */
class RESplitter
{
public:
  explicit RESplitter(const std::string& pattern, int cflags = 0)
    : pattern(pattern), source(""), matched(false), ss(0), se(0)
  {
    int rc = regcomp(&preg, pattern.c_str(), cflags | REG_EXTENDED);
    if (rc != 0)
      {
        char errbuf[256];
        regerror(rc, &preg, errbuf, sizeof(errbuf));
        throw ("RESplitter: invalid pattern \"" + pattern + "\": " + errbuf);
      }
  }

  ~RESplitter()
  {
    regfree(&preg);
  }

  RESplitter(const RESplitter&)            = delete;
  RESplitter& operator=(const RESplitter&) = delete;

  // ---------------------------------------------------------------------- //

  /** Sucht das Muster im String. @return true bei match. */
  bool setSource(const std::string& s)
  {
    source  = s;

    regmatch_t pm;

    matched = regexec(&preg, source.c_str(), 1, &pm, 0) == 0;
    if (matched)
      {
        ss      = pm.rm_so;
        se      = pm.rm_eo;
      }
    return matched;
  }

  std::string before() const
  {
    requireMatch();
    return source.substr(0, static_cast<std::size_t>(ss));
  }

  std::string match()  const
  {
    requireMatch();
    return source.substr(static_cast<std::size_t>(ss), static_cast<std::size_t>(se - ss));
  }

  std::string after()  const
  {
    requireMatch();
    return source.substr(static_cast<std::size_t>(se));
  }

private:
  std::string pattern;
  std::string source;
  regex_t     preg;
  bool matched;
  regoff_t    ss, se;

  void requireMatch() const
  {
    if (!matched)
      throw std::logic_error("RESplitter: no match");
  }
};

#endif // RESPLITTER
