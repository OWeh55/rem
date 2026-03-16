#ifndef REGEXSPLIT_H
#define REGEXSPLIT_H

#include <stdexcept>
#include <string>

#include <sys/types.h>
#include <regex.h>

/**
 * Schlanker C++-Wrapper fuer POSIX Extended Regular Expressions.
 *
 * Ein Muster, ein Treffer. Ergebnis: before() / match() / after().
 *
 * Hinweis: POSIX ERE kennt kein \d oder \w --
 *          stattdessen [[:digit:]], [[:alpha:]] usw. verwenden.
 *
 * Beispiel:
 *   RegexSplit re("[[:digit:]]+");
 *   if (re.setSource("Preis: 42 Euro"))
 *       std::cout << re.match();  // "42"
 */
class RegexSplit
{
public:
  explicit RegexSplit(const std::string& pattern, int cflags = 0)
    : pattern(pattern), matched(false), ss(0), se(0)
  {
    int rc = regcomp(&preg, pattern.c_str(), cflags | REG_EXTENDED);
    if (rc != 0)
      {
        char errbuf[256];
        regerror(rc, &preg, errbuf, sizeof(errbuf));
        throw ("RegexSplit: invalid pattern \"" + pattern + "\": " + errbuf);
      }
  }

  ~RegexSplit()
  {
    regfree(&preg);
  }

  RegexSplit(const RegexSplit&)            = delete;
  RegexSplit& operator=(const RegexSplit&) = delete;

  // ---------------------------------------------------------------------- //

  /** Sucht das Muster im String. @return true bei Treffer. */
  bool setSource(const std::string& s)
  {
    source  = s;
    matched = false;

    regmatch_t pm;
    if (regexec(&preg, source.c_str(), 1, &pm, 0) == 0)
      {
        ss      = pm.rm_so;
        se      = pm.rm_eo;
        matched = true;
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
  bool        matched;
  regoff_t    ss, se;

  void requireMatch() const
  {
    if (!matched)
      throw std::logic_error(
        "RegexSplit: no match -- check setSource()");
  }
};

#endif // REGEXSPLIT_H
