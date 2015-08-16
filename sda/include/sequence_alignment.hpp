////////////////////////////////////////////////////////////////////////////////
// 
// sequence_alignment.hpp
//
// Needleman-Wunsch algorithm
//
// Melanie Tosik (759476)
// 11-8-2015
//
// Compiled with 
//  clang:  Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn)
//  gcc:    gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
////////////////////////////////////////////////////////////////////////////////

#ifndef SEQUENCE_ALIGNMENT_hpp
#define SEQUENCE_ALIGNMENT_hpp

#include <string>
#include <vector>
#include <algorithm>

#define NDEBUG
#include <cassert>

/// Define a matrix as a vector of vectors
typedef std::vector<std::vector<size_t> > Matrix;

/// Compute global sequence alignment
class NeedlemanWunsch
{
public:
  /** 
    @brief Constructor: initialize member variables
    @param s1 First sequence 
    @param s2 Second sequence
  */
  NeedlemanWunsch (const std::string &s1, const std::string &s2)
  {
    // Sequence A
    seqA = s1;
    // Sequence B
    seqB = s2;
    // Length n of sequence A
    n = seqA.size();
    // Length m of sequence B
    m = seqB.size();
    // Matrix F[n+1][m+1]
    F = Matrix(n+1, std::vector<size_t>(m+1));
    // Gap penalty
    gap = -1;
    // Aligned sequence A
    alignA = "";
    // Aligned sequence B
    alignB = "";
  }

  /** 
    @brief Compute F matrix

    For two strings:  A of length n
                      B of length m

    We define F(i,j): the optimal score for the alignment of the first i = 0..n
                      characters in A and the first j = 0..m characters in B

    Once the F matrix is computed, the entry F(n,m) gives the maximum score
    among all possible alignments

    @see https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm
  */
  void compute_matrix() {
    // Basis
    // Initialize the first row to 0...n
    for (int i = 0; i <= n; i++) {
      F[i][0] = gap * i;
    };
    // Initialize the first column to 0...m
    for (int j = 0; j <= m; j++) {
      F[0][j] = gap * j;
    };
    // Recursion, based on the principle of optimality
    // For each row i from i..n
    for (int i = 1; i <= n; i++) {
      // For each column from j to j..m
      for (int j = 1; j <= m; j++) {
        // Match cost
        int match = F[i-1][j-1] + score(i,j);
        // Deletion cost
        int del = F[i-1][j] + gap;
        // Insertion cost
        int ins = F[i][j-1] + gap;
        // For each cell, F(i,j) contains maximum score among all paths
        F[i][j] = max(match,del,ins);
      }
    }
  }

  /** 
    @brief Compute alignment that gives score in F(n,m)

    To compute an alignment that gives score in F(n,m), start from the
    bottom right cell, and compare the value with the three possible
    sources (match, insert, and delete ) to see which it came from

    @note There can be alternative optimal alignments
    @note In this implementation, one a single best alignment is computed
    @see https://en.wikipedia.org/wiki/Needleman%E2%80%93Wunsch_algorithm
  */
  void trace_back() {
    int i = n;
    int j = m;
    // Maximum alignment score
    max_score = F[i][j];
    // Start at the end of the input sequences
    while (i > 0 || j > 0) {
      // If match, A[i] and B[j] are aligned    
      if ( i>0 && j>0 && F[i][j] == ( F[i-1][j-1] + score(i,j))) {        
        alignA += seqA[i-1];
        alignB += seqB[j-1];
        i--;
        j--;        
      }
      // If delete, A[i] is aligned with a gap
      else if ( i>0 && F[i][j] == F[i-1][j] + gap) {
        alignA += seqA[i-1];
        alignB += "-";
        i--;
      }
      // If insert, B[j] is aligned with a gap
      else {
        alignA += "-";
        alignB += seqB[j-1];
        j--;
      }
    }
    // Reverse aligned sequences
    std::reverse(alignA.begin(), alignA.end());
    std::reverse(alignB.begin(), alignB.end());
  }

  /** 
    @brief Print F matrix to std::cout
    @note Doesn't get called, but might come in handy
  */
  void print_matrix () {
    // Iterate over F matrix
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        // Display the current element 
        std::cout << F[i][j] << "\t"; 
      }
    // Go to new line when the inner loop is done
    std::cout << std::endl;
    }
  }

  // Print maximum alignment score and single best alignment
  void print_alignment () {
    std::cout << "Sequence A: " << alignA << "\n";
    std::cout << "Sequence B: " << alignB << "\n";
    std::cout << "Maximum alignment score: " << max_score << "\n\n";
  }  

private: // Private functions
    
  /** 
    @brief Compute weighting scores
    @param i position in A
    @param j position in B
  */
  const int score(int i, int j) {
    // If A[i] equals B[j], return match score
    // Else return mismatch score
    return (seqA[ i-1 ] == seqB[ j-1 ] ? 1 : -1);
  }
 
private: // Private attributes, accessible only from within the class

  std::string seqA, seqB;     ///< Sequence A, sequence B
  std::string alignA, alignB; ///< Aligned sequence A, aligned sequence B
  int n, m;                   ///< Length n of A, length m of B
  int gap;                    ///< Gap penalty
  Matrix F;                   ///< F matrix
  int max_score;              ///< Maximum alignment score

};
#endif