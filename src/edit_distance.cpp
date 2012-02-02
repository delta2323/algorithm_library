#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int EditDistance(const string& s, const string& t) {
  int n = s.size();
  int m = t.size();
  vector<vector<int> > dp(n+1, vector<int>(m+1));

  for(int i = 0; i <= n; i++) {
    dp[i][0] = i;
  }

  for(int i = 0; i <= m; i++) {
    dp[0][m] = i;
  }

  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= m; ++j) {
      int cost = s[i-1] == t[j-1] ? 0 : 1;
      dp[i][j] = min(min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]+cost);
    }
  }
  return dp[n][m];
}
