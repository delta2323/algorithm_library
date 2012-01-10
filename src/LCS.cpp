#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "../print.hpp"

using namespace std;

/**
 * @brief calculate longest common sequence of given two strings
 * (vector<A> is also is also acceptable)
 */
template <typename T>
class LCS{
private:
  /**
   * @field sa,sb : given two strings
   * @field C     : table for calculating LCS
   */
  T sa;
  T sb;
  vector<vector<size_t> > C;

  /**
   * method : all_CS(size_t i, size_t j)
   * @brief : return the list of sequences which are contained in both 
   *          in sa[0,i) and sb[0,j)
   * (Note that all_CS is supposed to be called from all_CS() and 
   *  not called from outside of class )
   *          this algorithm is a kind of dfs.
   * @return      : list of 
   * @param  i,j  : positions that separate subsequences
   */
  vector<T > all_CS(size_t i, size_t j){
    if(i == 0 || j == 0){
      vector<T > dummy;
      return dummy;
    }else if(sa[i-1] == sb[j-1]){
      vector<T > ret = all_CS(i-1,j-1);
      for(size_t k = 0;k<ret.size();k++){
	ret[k].push_back(sa[i-1]);
      }
      T buf(1,sa[i-1]);
      ret.push_back(buf);
      return ret;
    }else{
      vector<T > ret;
      if(C[i][j-1] >= C[i-1][j] ){
	ret = all_CS(i,j-1);
      }
      if(C[i-1][j] >= C[i][j-1]){
	vector<T > append = all_CS(i-1,j);
	for(size_t i = 0;i<append.size();i++){
	  ret.push_back(append[i]);
	}
      }
      return ret;
    }
  }

public:
  /**
   * @brief : constructor
   *          length of longest susequence is calculated in this constructor
   * @param _sa,_sb : two sequence 
   */

  LCS(T & _sa, T & _sb): sa(_sa), sb(_sb){
    C.resize(sa.size()+1);
    for(size_t i = 0;i<C.size();i++){
      C[i].resize(sb.size()+1);
    }
    for(size_t  i = 1;i<=sa.size();i++){
      for(size_t j = 1;j<=sb.size();j++){
	if(sa[i-1] == sb[j-1]){
	  C[i][j] = C[i-1][j-1]+1;
	}else{
	  C[i][j] = C[i][j-1] > C[i-1][j] ? C[i][j-1] : C[i-1][j];
	}
      }
    }    
  }

  /**
   * @brief return the list of sub sequences
   *        which are contained both sa and sb
   * ( Note that this function can take exponential time 
   *  with respect to the length of sa and sb )
   */
  vector<T > all_CS(){
    vector<T > ret = all_CS(sa.size(), sb.size());
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(),ret.end()),ret.end());
    return ret;
  }

  /**
   * @beief retrurn the length of longest common subsequece of sa and sb
   */
  size_t LCSlength(){
    return C[sa.size()][sb.size()];
  }

};

int main(){
  srand((unsigned) time(NULL));
  vector<int> a(5);
  for(int i = 0;i<5;i++){
    a[i] = rand()%10;
  }
  vector<int> b(6);
  for(int i = 0;i<6;i++){
    b[i] = rand()%10;
  }
  print(a),print(b);
  
  LCS<vector<int> > lcs(a,b);
  print(lcs.all_CS());
  cout<<lcs.LCSlength() << endl;

  string s(10,' ');
  for(int i = 0;i<10;i++){
    s[i] = 'a' + rand()%10;
  }
  string t(15,' ');
  for(int i = 0;i<15;i++){
    t[i] = 'a' +  rand()%10;
  }
  LCS<string> l(s,t);
  print(s),print(t);
  print(l.all_CS());


}
