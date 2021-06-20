#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <iterator>
#include "bst.hpp"

template<typename T>
  void debug(T);

int main(){

  bst<int, char> pippo;
  std::pair<int, char> a = std::make_pair(1, 'a');
  
  auto d = pippo.insert(a);

  auto c = d.second;  
  
  std::cout<< c << std::endl;  
  
  auto b = pippo.insert(a);

  auto e = b.second;

  std::cout<< e << std::endl;
  return 0;
}
