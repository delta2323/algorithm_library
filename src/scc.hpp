#include <iostream>
#include <vector>

class SCC {
public:
  SCC(const std::vector<std::vector<int> >& adj);
  void execute();
  void get_scc_idx(std::vector<int>& scc_idx);
  void get_scc_list(std::vector<std::vector<int> >& scc_list);
private:
  void dfs(int now);
  void dfs2(int now, int scc_idx);
  int n_;
  std::vector<std::vector<int> > adj_;
  std::vector<std::vector<int> > rev_;
  std::vector<int> post_order_;
  std::vector<bool> labelled_;
  std::vector<bool> in_scc_;

  std::vector<std::vector<int> > result_;
  std::vector<int> result2_;
};
