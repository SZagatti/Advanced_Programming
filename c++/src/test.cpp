#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <iterator>
#include "bst.hpp"

int main(){

  bst<int, char> pippo;
  std::pair<int, char> a = std::make_pair(1, 'a');
  
  pippo.insert(a);  
  pippo.insert(std::pair<int, char>(2, 'b'));
  pippo.insert(std::pair<int, char>(3, 'c'));
  pippo.insert(std::pair<int, char>(4, 'd'));

  std::cout << "pippo\n" << pippo << std::endl;
  pippo.balance();
  
  //auto b = pippo.find(5);

  //if( b != pippo.end()){ std::cout << (*b).first << std::endl; 

  //  }else if( b == pippo.end() ){ std::cout << "nullptr" << std::endl; 
    
  //  }else{ std::cout << "unknwn" << std::endl; }


  // std::cout << pippo[2] << std::endl;
  
  // int c = 3;
  
  // std::cout << pippo[c] << std::endl;

  auto pluto{pippo};  // copy ctor

  std::cout << "pluto\n" << pluto << std::endl;

  pippo.emplace(5, 'e');

  pluto.emplace(6, 'f');

  std::cout << "pippo\n" << pippo << std::endl;
  std::cout << "pluto\n" << pluto << std::endl;

  bst<int, char> paperino;
  
  paperino = pippo; // copy assign

  std::cout << "paperino\n" << paperino << std::endl;
  
  auto topolino{std::move(pluto)}; // move ctor

  std::cout << "topolino\n" << topolino << std::endl;

  bst<int, char> minnie;
  
  minnie = std::move(pippo);

  std::cout << "minnie\n" <<  minnie << std::endl;

  std::cout << "pippo\n" << pippo << std::endl;

  std::cout << " =============================================" << std::endl;

  bst<int, char> tree;

  tree.insert(std::pair<int, char>(8, 'h'));
  tree.insert(std::pair<int, char>(3, 'c'));
  tree.insert(std::pair<int, char>(10, 'l'));
  tree.insert(std::pair<int, char>(1, 'a'));
  //tree.insert(std::pair<int, char>(9, 'i'));
  tree.insert(std::pair<int, char>(6, 'f'));
  tree.insert(std::pair<int, char>(14, 'p'));
  tree.insert(std::pair<int, char>(4, 'd'));
  tree.insert(std::pair<int, char>(13, 'q'));
  tree.insert(std::pair<int, char>(7, 'g'));


  tree.erase(8);
  
  tree.print();

  //bst<int, char> t;
  //t.insert(std::pair<int, char>(8, 'h'));
  //t.insert(std::pair<int, char>(7, 'h'));
  //t.insert(std::pair<int, char>(6, 'h'));

  //t.erase(8);

  //t.print();
  //std::cout << "\n" << t << std::endl;

  return 0;
}
