#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using namespace std;

// using std::map
// using std::

// Numerical sort 
struct sort_helper{
  bool operator()(const pair<string,int> lhs, const pair<string,int> rhs) const {
    // Descending order
    return lhs.second > rhs.second;
    // // Ascending order
    // return lhs.second < rhs.second;
    }
};


int main(int argc, const char *argv[])
{
  ifstream infile(argv[1]);

  if (argc != 2) {
    cerr << "Usage: sort_types <file>\n";
  }

  map<string,int> word_count;
  string word;

  while (infile >> word){
    // Remove punctuation
    for(size_t i=0; i<word.length(); ++i)
      if(ispunct(word[i])) word.erase(i--, 1);
    if (!word.empty()) {
      // Count word type frequency
      ++word_count[word];
    }
  }

  // // Print word_count<key,value>
  // for(map<string,int>::iterator it=word_count.begin(); it!=word_count.end(); ++it) {
  // cout << it->first << "\t\t\t" << it->second << "\n";
  // }

  vector<pair<string,int> > word_vector;
  copy(word_count.begin(), word_count.end(), back_inserter(word_vector));

  sort(word_vector.begin(),word_vector.end(),sort_helper());

  // for (auto t=type_freq_iters.begin(); t!=type_freq_iters.end(), TypeCmpByFreq()) {
  //   cout << (*t)->second << "\t" << (*t)->first << endl;
  // }

  for(int i=0; i<word_vector.size(); ++i)
  // for(int i=0; i<20; ++i)
    cout << setw(5) << left << word_vector[i].second << " " << word_vector[i].first << endl;
    // cout << word_vector[i].first << "\n";
}
