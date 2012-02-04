#include <string>
#include <vector>

#include "kmp.hpp"

using namespace std;

KMP::KMP(const string& key_) {
  key = key_;
  table.push_back(-1);
  table.push_back(0);
  int i = 2;
  int j = 0;
  while(i == 0 || i-1 < (int)key.size()) {
    if(key[i-1] == key[j]) {
      table.push_back(++j);
      ++i;
    }else if(j > 0) {
      j = table[j];
    }else {
      table.push_back(0);
      ++i;
    }
  }
}

vector<int> KMP::search(const string& str, vector<int >& ret){
  int i = 0;
  int j = 0;
  while(i < (int)str.size()) {
    if(str[i] == key[j]) {
      if(j+1 >= (int)key.size()) {
	ret.push_back(i-j);
      }
      ++i; ++j;
    }else if(j > 0) {
      j = table[j];
    }else {
      ++i;
    }
  }
  return ret;
}

int KMP::search_one(const string& str){
  int i = 0;
  int j = 0;
  while(i < (int)str.size()) {
    if(str[i] == key[j]) {
      if(j+1 >= (int)key.size()) {
	return i-j;
      }
      ++i; ++j;
    }else if(j > 0) {
      j = table[j];
    }else {
      ++i;
    }
  }
  return -1;
}
