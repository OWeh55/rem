#include "filter.h"

#include <iostream>

using namespace std;
#include <string>
#include <stdexcept>
#include <algorithm>

/**
 * Expandiert ein Zeichenmuster in einen String mit allen enthaltenen Zeichen.
 *
 * Unterstützte Elemente (direkt hintereinander):
 *  - Einzelne Literale:      a  B  3  _
 *  - Bereiche:               a-z  A-Z  0-9  3-9
 *  - POSIX-Klassen:          [:digit:]  [:alpha:]  [:alnum:]  [:space:]
 *
 * Beispiele:
 *  "asd3-9[:digit:]"        -> 'a','s','d','3'..'9','0'..'9'
 *  "A-F[:digit:]g"          -> 'A'..'F','0'..'9','g'
 *  "[:alpha:].[:space:]"    -> Buchstaben, '.', Whitespace
 */

// ---------------------------------------------------------------------------
// Hilfsfunktion: expandiert eine POSIX-Klasse [:name:] in einen String
// ---------------------------------------------------------------------------
static std::string expandPosixClass(const std::string& name)
{
  if (name == "digit")
    {
      return "0123456789";
    }
  if (name == "alpha")
    {
      std::string s;
      for (unsigned char c = 'A'; c <= 'Z'; ++c) s += static_cast<char>(c);
      for (unsigned char c = 'a'; c <= 'z'; ++c) s += static_cast<char>(c);
      return s;
    }
  if (name == "alnum")
    {
      std::string s;
      for (unsigned char c = '0'; c <= '9'; ++c) s += static_cast<char>(c);
      for (unsigned char c = 'A'; c <= 'Z'; ++c) s += static_cast<char>(c);
      for (unsigned char c = 'a'; c <= 'z'; ++c) s += static_cast<char>(c);
      return s;
    }
  if (name == "space")
    {
      return " \t\n\r\f\v";
    }

  throw std::invalid_argument("Unbekannte POSIX-Klasse: [:" + name + ":]");
}

// ---------------------------------------------------------------------------

std::string Filter::expandCharSet(const std::string& pattern)
{
  std::string result;

  for (size_t i = 0; i < pattern.size();)
    {
      // --- POSIX-Klasse: [:name:] ---
      if (i + 1 < pattern.size() && pattern[i] == '[' && pattern[i + 1] == ':')
        {
          size_t close = pattern.find(":]", i + 2);
          if (close == std::string::npos)
            throw std::invalid_argument(
              "Nicht geschlossene POSIX-Klasse ab Position " + std::to_string(i));

          result += expandPosixClass(pattern.substr(i + 2, close - (i + 2)));
          i = close + 2;
        }
      // --- Bereich: X-Y ---
      else if (i + 2 < pattern.size() && pattern[i + 1] == '-' && pattern[i + 2] != '[')
        {
          unsigned char start = static_cast<unsigned char>(pattern[i]);
          unsigned char end   = static_cast<unsigned char>(pattern[i + 2]);

          if (start > end)
            throw std::invalid_argument(
              std::string("Ungültiger Bereich: ") + pattern[i] + "-" + pattern[i + 2]);

          for (unsigned char c = start; c <= end; ++c)
            result += static_cast<char>(c);

          i += 3;
        }
      // --- Literal-Zeichen ---
      else
        {
          result += pattern[i++];
        }
    }

  return result;
}
