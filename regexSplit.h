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
    : pattern_(pattern), matched_(false), ss_(0), se_(0)
  {
    int rc = regcomp(&preg_, pattern_.c_str(), cflags | REG_EXTENDED);
    if (rc != 0)
      {
        char errbuf[256];
        regerror(rc, &preg_, errbuf, sizeof(errbuf));
        throw ("RegexSplit: invalid pattern \"" + pattern_ + "\": " + errbuf);
      }
  }

  ~RegexSplit()
  {
    regfree(&preg_);
  }

  RegexSplit(const RegexSplit&)            = delete;
  RegexSplit& operator=(const RegexSplit&) = delete;

  // ---------------------------------------------------------------------- //

  /** Sucht das Muster im String. @return true bei Treffer. */
  bool setSource(const std::string& s)
  {
    source_  = s;
    matched_ = false;

    regmatch_t pm;
    if (regexec(&preg_, source_.c_str(), 1, &pm, 0) == 0)
      {
        ss_      = pm.rm_so;
        se_      = pm.rm_eo;
        matched_ = true;
      }
    return matched_;
  }

  std::string before() const
  {
    requireMatch();
    return source_.substr(0, static_cast<std::size_t>(ss_));
  }
  std::string match()  const
  {
    requireMatch();
    return source_.substr(static_cast<std::size_t>(ss_), static_cast<std::size_t>(se_ - ss_));
  }
  std::string after()  const
  {
    requireMatch();
    return source_.substr(static_cast<std::size_t>(se_));
  }

private:
  std::string pattern_;
  std::string source_;
  regex_t     preg_;
  bool        matched_;
  regoff_t    ss_, se_;

  void requireMatch() const
  {
    if (!matched_)
      throw std::logic_error(
        "RegexSplit: no match -- check setSource()");
  }
};

#endif // REGEXSPLIT_H
