#include "filter.h"

#include <iostream>

using namespace std;
#include <string>
#include <stdexcept>
#include <algorithm>

/**
 * Expandiert eine RegExp-Zeichenklasse wie "[a-zA-Z0-9]" in einen String
 * mit allen enthaltenen Zeichen.
 *
 * Unterstützt:
 *  - Bereiche wie a-z, A-Z, 0-9
 *  - Einzelne Zeichen
 *  - Optionale eckige Klammern
 *
 * Beispiele:
 *  "[a-zA-Z]"  -> "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
 *  "[0-9]"     -> "0123456789"
 *  "A-Fa-f0-9" -> "ABCDEFabcdef0123456789"
 */

std::string Filter::expandCharSet(const std::string& pattern)
{
  // Eckige Klammern entfernen, falls vorhanden
  std::string p = pattern;
  if (p.size() >= 2 && p.front() == '[' && p.back() == ']')
    p = p.substr(1, p.size() - 2);

  std::string result;
  size_t i = 0;

  while (i < p.size())
    {
      // Bereich erkennen: X-Y  (mindestens 3 Zeichen übrig, mittleres ist '-')
      if (i + 2 < p.size() && p[i + 1] == '-')
        {
          unsigned char start = static_cast<unsigned char>(p[i]);
          unsigned char end   = static_cast<unsigned char>(p[i + 2]);

          if (start > end)
            throw std::invalid_argument(
              std::string("Ungültiger Bereich: ") + p[i] + "-" + p[i + 2]);

          for (unsigned char c = start; c <= end; ++c)
            result += static_cast<char>(c);

          i += 3;
        }
      // Literal '-' am Ende des Musters (kein Bereich möglich)
      else
        {
          result += p[i];
          ++i;
        }
    }

  return result;
}
