#ifndef PRINT_HPP_
#define PRINT_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <set>

void print(int);
void prin(double);
void print(long long);
void print(const std::string&);
template<typename T> void print (const std::set<T>&);
template<typename T> void print (const std::vector<T>&);
template<typename T, typename U> void print (const std::pair<T, U>&);
template<typename T, typename U> void print (const std::map<T, U>&);

void print (int n){
  std::cout << n;
}

void print (double n){
  std::cout << n;
}

void print (long long n){
  std::cout << n;
}

void print (const std::string& n){
  std::cout << "\"" << n << "\"" << std::endl;
}

template<typename T>
void print (const std::set<T>& n){
  typedef typename std::set<T>::const_iterator ittype;
  std::cout << "{" ;
  for(ittype it = n.begin(); it != n.end(); it++){
    std::cout << *it << std::endl;
  }
  std::cout << "}" << std::endl;
}

template <typename T>
void print (const std::vector<T>& n){
  std::cout << "[";
  for(size_t i=0;i<n.size();i++){
    print(n[i]);
    std::cout << " ";
  }
  std::cout << "]"  << std::endl;
}

template <typename T, typename U>
void print (const std::pair<T, U>& n){
  std::cout << "(";
  print(n.first);
  std::cout << ",";
  print(n.second);
  std::cout << ")" << std::endl;
}

template <typename T, typename U>
void print (const std::map<T, U>& n){
  typedef typename std::map<T, U>::const_iterator ittype;
  for(ittype it = n.begin(); it != n.end(); it++){
    print (it->first);
    std::cout << "->" ;
    print (it->second);
    std::cout << ", " << std::endl;
  }
  std::cout << std::endl;
}


#endif // PRINT_HPP_
