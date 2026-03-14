#include <string>
#include <iostream>
#include "reWrapper.h"

int main()
{
  REWrapper re("b.*xc",0);
  re.setSource("abcdefgh");
  std::cout << re.before() << " # " << re.match() << " # " << re.after() << std::endl;
    
}
