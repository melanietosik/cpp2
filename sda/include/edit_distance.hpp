////////////////////////////////////////////////////////////////////////////////
// 
// edit_distance.hpp
//
// Hamming Distance
// Minimum edit Distance
// Levenshtein Distance
//
// Wagner-Fischer algorithm
//
// Melanie Tosik (759476)
// 11-8-2015
//
// Compiled with 
//  clang:  Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn)
//  gcc:    gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
////////////////////////////////////////////////////////////////////////////////

#ifndef STRING_DISTANCE_hpp
#define STRING_DISTANCE_hpp

#include <string>
#include <vector>
#include <algorithm>

#define NDEBUG
#include <cassert>

/// Define a matrix as a vector of vectors
typedef std::vector<std::vector<size_t> > Matrix;

/// Compute edit distances
class EditDistance 
{
public:
  /** 
    @brief Constructor: initialize member variables
    @param s1 First sequence 
    @param s2 Second sequence
  */
  EditDistance (const std::string &s1, const std::string &s2)
  {
    // Sequence A
    seqA = s1;
    // Sequence B
    seqB = s2;
    // Length n of sequence A
    n = seqA.size();
    // Length m of sequence B
    m = seqB.size();
    // Edit distance
    dist = 0;
  }

  /** 
    @brief Compute Hamming distance between two given strings

    The Hamming distance between two strings of equal length is the number
    of positions at which the corresponding characters are different

    @param s1 First string
    @param s2 Second string
    @return Hamming distance between s1 and s2
    @see https://en.wikipedia.org/wiki/Hamming_distance
  */
  int hamming_distance (const std::string &s1, const std::string &s2) {
    assert(n == m);
    // Hamming distance is restricted to equal-length strings
    if (n != m) {
      std::cerr << "Strings passed to hamming_distance() must be of equal length. Exiting.\n";
      exit(1);
    }
    // Iterate over both strings simultaneously and compare character pairs
    else {
      // For as long as there are characters
      for (unsigned i = 0; i < n; i++ ) {
        // Compare characters at position i
        // If A[i] doesn't equal B[i], increment string distance by 1
        if (seqA[i] != seqB[i]) dist++;
      }
      if (seqA == seqB) assert(dist == 0);
      assert(dist <= (n));
      // Return edit distance
      return dist;
    }
  }

  /** 
    @brief Compute minimum edit distance between two strings

    The minimum edit distance between two strings is the minimum number of
    single-character edits (insertion, deletion, substitution) required to
    transform one string into another

    @param s1 First string
    @param s2 Second string
    @return Minimum edit distance between s1 and s2
    @see https://en.wikipedia.org/wiki/Edit_distance
    @note In this implementation, each editing operation has a cost of 1
  */
  int minimum_edit_distance(const std::string &s1, const std::string &s2) {
    // If one string is empty string, return length of the other
    if (n == 0 || m == 0) return empty_string(s1,s2);
    // Computes Hamming distance if strings are of equal length
    else if (n == m) return hamming_distance(s1,s2);
    // Compute minimum edit distance
    else {
      // Initialize distance matrix
      init_matrix();
      // Compute edit distance with a substitution cost of 1
      return compute_matrix(1);
    }
  }

  /** 
    @brief Compute Levenshtein distance between two strings

    The Levenshtein distance between two strings is the minimum number of
    single-character edits (insertion, deletion, substitution) required to
    transform one string into another

    @param s1 First string
    @param s2 Second string
    @return Levenshtein distance between s1 and s2
    @see https://en.wikipedia.org/wiki/Levenshtein_distance
    @note In this implementation, insertion and deletion have a cost of 1,
    and substitutions have a cost of 2 (one insertion, one deletion)
  */
  int levenshtein_distance(const std::string &s1, const std::string &s2) {
    // If one string is empty string, return length of the other
    if (n == 0 || m == 0) return empty_string(s1,s2);
    // Compute Levenshteindistance
    else {
      // Initialize distance matrix
      init_matrix();
      // Compute edit distance with a substitution cost of 2
      return compute_matrix(2);
    }
  }

  /** 
    @brief Print distance matrix to std::cout
    @note Doesn't get called, but might come in handy
  */
  void print_matrix () {
    // Iterate over distance matrix
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        // Display the current element 
        std::cout << D[i][j] << "\t"; 
      }
    // Go to new line when the inner loop is done
    std::cout << std::endl;
    }
  }

private: // Private functions

  /** 
    @brief Initialize Wagner-Fischer algorithm

    For two strings:  A of length n
                      B of length m

    We define D(i,j): the edit distance between A[1..i] and B[1..j], i.e.
                      the edit distance between the first i characters in
                      A and the first j characters in B

    Thus, the edit distance between A and B is D(n,m)

    @see https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
  */ 
  void init_matrix() {
    // Create distance matrix D[n+1][m+1]
    D = Matrix(n+1, std::vector<size_t>(m+1));
    // Initialize the first row to 0...n
    for (int i = 0; i <= n; i++) {
      D[i][0] = i; // Distance of any first string to an empty second string
    };
    // Initialize the first column to 0...m
    for (int j = 0; j <= m; j++) {
      D[0][j] = j; // Distance of any second string to an empty first string
    }; 
  }

  /** 
    @brief Calculate Wagner-Fischer algorithm

    Iterative computation of edit distance using a full matrix

    @note Algorithm can be applied to Minimum Edit and Levenshtein distance
    @param sub_cost Substitution cost
    @see https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm
  */
  int compute_matrix(int sub_cost) {
    // Recurrence relation
    // For each row i from i..n
    for (int i = 1; i <= n; ++i) {
      // For each column from j to j..m
      for (int j = 1; j <= m; ++j) {
        // Insertion cost
        size_t ins = D[ i-1 ][j] + 1;
        // Deletion cost
        size_t del = D[i][ j-1 ] + 1;
        // Substitution cost
        // If A[i] equals B[j], the cost is 0
        // If A[i] doesn't equal B[j], the cost depends on the distance metric
        size_t sub = D[ i-1 ][ j-1 ] + (seqA[ i-1 ] == seqB[ j-1 ] ? 0 : sub_cost);
        // Value of each cell is computed by taking the minimum of 3 possible paths
        // through the matrix which arrive here (insertion, deletion or substition)
        D[i][j] = min(ins,del,sub);
      }
    }
    // Assert upper and lower bounds
    assert(dist >= (n - m) || (m - n));
    assert(dist <= ((n >= m) ? n : m));
    if (seqA == seqB) assert(dist == 0);
    // Termination
    // Edit distance is found in D(n,m)
    return dist = D[n][m];
  }

  /// If string is empty string, return length of the other string
  const int empty_string(const std::string &s1, const std::string &s2) {
    return ( n == 0 ? m : n);
  }

private: // Private attributes, accessible only from within the class

  std::string seqA, seqB; ///< Sequence A; sequence B
  size_t n, m;            ///< Length n of A; length m of B 
  Matrix D;               ///< Distance matrix D
  int dist, sub_cost;     ///< Edit distance; substituion cost

};
#endif