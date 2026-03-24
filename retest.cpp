#include "RESplitter.h"

#include <string>
#include <iostream>

int main(int argc, char** argv)
{
  std::string pattern = "a[[:alnum:]]+z";
  if (argc > 1)
    pattern = argv[1];
  std::string input;
  if (argc > 2)
    input = argv[2];
  else
    std::getline(std::cin, input);

  RESplitter re(pattern);
  if (re.setSource(input))
    {
      std::cout << "before: " << re.before() << std::endl;
      std::cout << "match: " << re.match() << std::endl;
      std::cout << "after: " << re.after() << std::endl;
    }
  else
    std::cout << "no match" << std::endl;
}
