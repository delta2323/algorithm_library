#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include <vector>
#include <utility>
#include <limits>

class Dijkstra{
public:
  static const int UNREACHABLE;
  Dijkstra(){}
 //adj[source][i] = (dest, cost)
  void execute(const std::vector<std::vector<std::pair<int, int> > >& adj,
	       int start,
	       std::vector<int>& dist,
	       std::vector<int>& backward);
};

#endif
