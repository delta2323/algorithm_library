#ifndef KMP_HPP_
#define KMP_HPP_

#include <vector>
#include <string>

class KMP {
  /**
   * class KMP
   * an implementation of KMP search
   * 
   * thanks qnighy for original implementation of kmp search
   * http://d.hatena.ne.jp/qnighy/20100117/1263734784
   */

public:
  /**
   * constructor KMP(string _key)
   *   @param _key : the word we are looking for from documents
   */
  KMP(const std::string& key_);
  /**
   * method search
   *   @return void<int> : return the list of hit position (0-indexed)
   *   @param str  : target document which is to be searched
   *   @param ret  : indentical to return value
   */
  std::vector<int> search(const std::string& str, std::vector<int>& ret);
  int search_one(const std::string& str);
private:
  /**
   * @field table : a table which helps kmp search 
   * @field key   : the word we are looking for from documents
   */
  std::vector<int > table;
  std::string key;
};

#endif
