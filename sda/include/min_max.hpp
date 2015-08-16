////////////////////////////////////////////////////////////////////////////////
// 
// min_max.hpp
// 
// Template for finding the minimum value out of three values
// Template for finding the maximum value out of three values
//
// Melanie Tosik (759476)
// 11-8-2015
//
// Compiled with 
// 	clang: Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn)
//  gcc:   gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
////////////////////////////////////////////////////////////////////////////////

/// Now works on all types supporting operator "<"

/// Find minimum
template<class T> T min(T x, T y, T z) {
    return x < y ? std::min( x , z) : std::min( y , z);
}

/// Find maximum
template<class T> T max(T x, T y, T z) {
    return x > y ? std::max( x , z) : std::max( y , z);
}