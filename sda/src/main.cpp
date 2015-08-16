////////////////////////////////////////////////////////////////////////////////
// 
// main.cpp
// 
// Edit distance
// Sequence alignment
//
// Melanie Tosik (759476)
// 15-8-2015
//
// Compiled with 
//  clang: Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn)
//  gcc:   gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

#include <unistd.h>
#include <stdlib.h>

#include "../include/min_max.hpp"
#include "../include/edit_distance.hpp"
#include "../include/sequence_alignment.hpp"

/// Display usage information
void print_help(char *p) {
  std::cout << "Usage:      " << p << " [-option] [sequence1] [sequence2]" << std::endl;
  std::cout << "Option:     " << "-m  Compute minimum edit distance" << std::endl;
  std::cout << "            " << "-l  Compute levenshtein distance" << std::endl;
  std::cout << "            " << "-a  Compute global sequence alignment" << std::endl;
  std::cout << "            " << "-h  Print help message" << std::endl;
  std::cout << "Example:    " << p << " -l insertion execution" << std::endl;
  std::cout << "Note:       " << "Input sequences are case sensitive" << std::endl;
}

int main(int argc, char* argv[])
{
  char tmp;
  /// If the program is ran with too few or too many options,
  /// display usage information and exit
  if (argc == 1 || argc == 2 || argc >= 5) {
    print_help(argv[0]);
    exit(1);
  }
  /// Use getopt() to get arguments with option
  while((tmp = getopt (argc, argv, "m:l:a:h")) != -1) {
    // Initialize input sequences
    std::string s1, s2;
    s1 = "";
    s2 = "";
    // If 3 arguments are given, second string is empty string
    if (argc == 3 ) {
      s1 = argv[2];
      s2 = "";
    }
    // If 4 arguments are given, process two strings
    else if (argc == 4 ) {
      s1 = argv[2];
      s2 = argv[3];
    }

    switch(tmp) {

      /* Minimum edit distance */
      { case 'm':
        EditDistance d(s1,s2);
        std::cout << "Minimum edit distance: " << d.minimum_edit_distance(s1,s2) << std::endl << std::endl;
        return 0; } 

      /* Levenshtein distance */
      { case 'l':
        EditDistance d(s1,s2);
        std::cout << "Levenshtein distance: " << d.levenshtein_distance(s1,s2) << std::endl << std::endl;
        return 0; } 

      /* Needleman-Wunsch alignment */
      { case 'a':
        NeedlemanWunsch nw(s1,s2);
        nw.compute_matrix();
        nw.trace_back();
        nw.print_alignment();
        return 0; } 

      /// Display usage information by default
      default:
        print_help(argv[0]);
        return 1;
    }
  return 0;
  }
}