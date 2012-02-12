#ifndef KMP_HPP_
#define KMP_HPP_

#include <vector>
#include <string>

class ZAlg {
public:
  ZAlg(const std::string& s);
  int get(int pos);
private:
  std::vector<int > z;
};

#endif
