#include <cstdio>
#include <string>
#include <vector>
#include "print.hpp"

using namespace std;


class KMP{
  /**
   * class KMP
   * an implementation of KMP search
   * 
   * thanks qnighy for original implementation of kmp search
   * http://d.hatena.ne.jp/qnighy/20100117/1263734784
   */
private:
  /**
   * @field table : a table which helps kmp search 
   * @field key   : the word we are looking for from documents
   */
  std::vector<int > table;
  std::string key;
public:

  /**
   * constructor KMP(string _key)
   *   @param _key : the word we are looking for from documents
   */
  KMP(std::string _key){
    key = _key;
    table.push_back(-1);
    table.push_back(0);
    int i=2,j=0;
    while(i==0 || key[i-1]) {
        if(key[i-1] == key[j]) {
	  table.push_back(++j);
	  i++;
        } else if(j>0) {
	  j = table[j];
        } else {
	  table.push_back(0);
	  i++;
        }
    }
  }  

  /**
   * method search
   *   @return void<int> : return the list of hit position (0-indexed)
   *   @param str  : target document which is to be searched
   *   @param ret  : indentical to return value
   */
  vector<int > search(std::string str, std::vector<int >& ret){
    int i=0,j=0;
    while(str[i]) {
      if(str[i]==key[j]) {
	if(!key[j+1]) {
	  ret.push_back(i-j);
	}
	i++, ++j;
        } else if(j>0) {
	j = table[j];
      } else {
	i++;
      }
    }
    return ret;
  }
};

int main(int argc, char **argv)
{
  string s = "ABCABCABCDABCABCDABCBCABCABCDABC";
  string key = "ABCABCDABC";
  vector<int > table;
  KMP kmp(key);

  kmp.search(s, table);
  for(size_t i = 0;i<table.size();i++){
    cout << table[i] <<" " ;
  }
 return 0;
}

