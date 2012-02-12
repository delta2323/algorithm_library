#include <string>
#include <vector>

#include "z_algorithm.hpp"

using namespace std;

// Original implementationn is 
// http://codeforces.com/blog/entry/3107

/* 
   z[i] is the length of longest common sequence of s and s[i].
   By definition z[0] = (length of s)
*/

ZAlg::ZAlg (const string& s) {
  int n = s.size();
  z.resize(n);
  z[0] = n;
  int L = 0, R = 0;
  for (int i = 1; i < n; i++) {
    if (i > R) {
      L = R = i;
      while (R < n && s[R-L] == s[R]) R++;
      z[i] = R-L; R--;
    } else {
      int k = i-L;
      if (z[k] < R-i+1) z[i] = z[k];
      else {
	L = i;
	while (R < n && s[R-L] == s[R]) R++;
	z[i] = R-L; R--;
      }
    }
  }
}

int ZAlg::get(int pos) {
  return z[pos];
}
