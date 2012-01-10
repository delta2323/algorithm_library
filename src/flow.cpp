#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <climits>

using namespace std;

/**
 * class Flow 
 * description : solve max-flow problem by using Dinic method
 * This class does not allow self-loop(i.e. an edge whose head and tail is 
 * an identical node. 
 * This class cannnot solve the max-flow of the graph whose 
 * start and terminating points are identical 
 */

class Flow{
private:
  /**
   * @struct edge : a struct that represents edge
   */ 
  struct edge{
    int to,cap,rev;
    edge(int _to, int _cap,int _rev):to(_to),cap(_cap),rev(_rev){}
    edge();
  };

  /**
   * @field _INF  : a constant that represents infimum
   * @field n     : the number of vetices
   * @field G     : adjacent matrix
   * @field level : distance from start point 
   *                (this field is used only when we call method max_flow )
   * @field iter  : for each vertex v, 0-iter[v] is visited
   *                (this field is used only when we call method max_flow )
   */
  int _INF;
  int n;
  vector<vector<edge> > G;
  vector<int > level;
  vector<int > iter;
  
  /**
   * @method bfs : breadth first search 
   *               (this field is used only when we call method max_flow )
   */
  void bfs(int s){
    level.clear();
    level.resize(n);
    for(int i = 0;i<n;i++){
      level[i] = -1;
    }
    queue<int > que;
    level[s] = 0;
    que.push(s);
    while(!que.empty()){
      int v = que.front();que.pop();
      for(int i = 0;i < G[v].size();i++){
	edge& e = G[v][i];
	if(e.cap > 0 && level[e.to] < 0 ){
	  level[e.to] = level[v] + 1;
	  que.push(e.to);
	}
      }
    }
    return;
  }

  /**
   * @method dfs : depth first search 
   *               (this field is used only when we call method max_flow )
   */
  int dfs(int v, int t, int f){
    if(v == t) {
      return f;
    }
    for(int& i = iter[v]; i < G[v].size();i++){
      edge &e = G[v][i];
      if(e.cap > 0 && level[v] < level[e.to]){
	int d = dfs(e.to, t, min(f,e.cap));
	if(d > 0){
	  e.cap -= d;
	  G[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }
  
public:
  /**
   * @description : constructor of class Flow
   * @param _n : intitializer of n
   */
  Flow(int _n):n(_n),_INF(1000000){
    G.resize(n);
  }

  /**
   * method add_edge :
   * @description : add directed edge with capatity to the graph
   * @param from  : the index of vertex from which the edge starts
   * @param to    : the index of vertex to which the edge reaches
   * @param cap   : the capacity of the edge
   */
  void add_edge(int from, int to, int cap){  
    if(from == to) {
      cerr << "loop (from = to) is not allowed" <<endl;
      return;
    }
    G[from].push_back(edge(to, cap, (int)G[to].size())) ;
    G[to].push_back(edge(from, 0, (int) G[from].size()-1));
    return;
  }


  /**
   * method max_flow : 
   * @description : calculate max-flow between two points 
   * @param s     : the start point of network flow
   * @param t     : the terminating point of network flow
   * @return      : maximum of flow that we can flow from s to t
   */  
  int max_flow(int s, int t){
    iter.clear();
    iter.resize(n);      
    int flow = 0;
    for(;;){
      bfs(s);
      if(level[t] < 0) return flow;
      iter.clear();
      iter.resize(n);      
      int f;
      while((f = dfs(s, t, _INF)) > 0){
	flow += f;
      }
    }  
  }  
};



int main(){ 
  /**
   * example of usese of class Flow
   *
   */ 
  Flow f(5);
  for(int i = 0;i<3;i++){
    f.add_edge(0,1,10);
    f.add_edge(0,2,2);
    f.add_edge(1,2,6);
    f.add_edge(1,3,6);
    f.add_edge(3,2,3);
    f.add_edge(2,4,4);
    f.add_edge(3,4,4);
  }
  cout <<f. max_flow(0,4) << endl;
  
}
