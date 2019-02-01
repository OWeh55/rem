#include <cstdlib>
#include <iostream>

#include "regexp.h"
#include "regexp_before.h"
#include "regexp_after.h"
#include "filtercascade.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc != 3)
    {
      cerr << " 2 Parameter: string und regex" << endl;
      exit(2);
    }

  vector<string> res;
  try
    {
      cout << "** regex: " ;
      RegExp re(argv[2], 0, true);
      re.print(cout);
      cout << endl;
      re.execute(argv[1], res);
      for (int i = 0; i < (int)res.size(); ++i)
        cout << i << ": >" << res[i] << "<" << endl;

      cout << "** regex-before: " ;
      RegExpBefore reb(argv[2], 0);
      reb.print(cout);
      cout << endl;
      reb.execute(argv[1], res);
      for (int i = 0; i < (int)res.size(); ++i)
        cout << i << ": >" << res[i] << "<" << endl;

      cout << "** regex-after: ";
      RegExpAfter rea(argv[2], 0);
      rea.print(cout);
      cout << endl;
      rea.execute(argv[1], res);
      for (int i = 0; i < (int)res.size(); ++i)
        cout << i << ": >" << res[i] << "<" << endl;
    }
  catch (const string& msg)
    {
      cerr << "Exception: " << msg << endl;
    }

}
