#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;


int main(int argc, const char *argv[])
{
  ifstream infile(argv[1]);

  if (argc != 2) {
    cerr << "Usage: clean_types <file> \n";
  }

  else {
    set<string> types;
    string input;

    while(getline(infile, input)) {
      // Remove punctuation
      for(size_t i=0; i<input.length(); ++i)
        if(ispunct(input[i])) input.erase(i--, 1);
      types.insert(input);
    }

    // Reverse order
    for (auto t=types.rbegin(); t!=types.rend(); ++t) {
      cout << *t << "\n"; 
    }
  }

}

