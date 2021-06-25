#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include "bst.hpp"
#include <map>
#include <chrono>
#include <fstream>
#include <random>
#include <algorithm>
#include <numeric>


int main(){

  unsigned int n_start{1000};	// starting number of nodes in the tree
  unsigned int n_max{100000};	// maximum number of nodes in the tree
  unsigned int n_incr{1000};	// increment
  unsigned int n_measures{50};  // number of measures for each step

  // open files
  std::ofstream outfile_tree;
  std::ofstream outfile_balanced;
  std::ofstream outfile_map;
 
  outfile_tree.open("src/benchmark_results/unbalanced_bst.txt");
  outfile_balanced.open("src/benchmark_results/balanced_bst.txt");
  outfile_map.open("src/benchmark_results/map.txt");

  // loop on the number of nodes

  for(unsigned int i{n_start}; i<=n_max; i += n_incr){

    std::vector<int> values(i);		// vector with i elements

    std::iota(std::begin(values), std::end(values), 1); // fill the vector with consecutive numbers starting from 1

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(values.begin(), values.end(), g);  //randomize vector

    // ========== BST ==========    

    bst<int, int> tree{};         	// empty binary search tree

    for(const auto& j : values){ 	// insert values inside binary search tree

      std::pair<int, int> pair{j,j};	// create pairs

      tree.insert(pair);		// insert pairs
    }

    
    // ========== BALANCED BST =========

    bst<int, int> balanced_tree{tree};

    balanced_tree.balance();		// balance the tree


    // ========== STD MAP ==========

    std::map<int, int> map{};

     for(const auto& j : values){ 	// insert values inside binary search tree

     std::pair<int, int> pair{j,j};

     map.insert(pair);
    }

    
    std::shuffle(values.begin(), values.end(), g);  //randomize again vector

    
    // measure the time:

    double treemean{0};
    
    for(unsigned int j = 1; j <= i/n_measures; ++j){
    
      auto treestart = std::chrono::high_resolution_clock::now();
    
        for( unsigned int k = (j-1)*n_measures; k<j*n_measures; ++k){
    
          tree.find(values[k]);
        }
    
     auto treeend = std::chrono::high_resolution_clock::now();
    
     treemean += std::chrono::duration_cast<std::chrono::nanoseconds>(treeend-treestart).count();
    }

    outfile_tree<< "\n" << i << "\t" << treemean/(i/n_measures);




    double balancedmean{0};
    
    for(unsigned int j = 1; j <= i/n_measures; ++j){

      auto balancedstart = std::chrono::high_resolution_clock::now();

        for( unsigned int k = (j-1)*n_measures; k<j*n_measures; ++k){

          balanced_tree.find(values[k]);
        }

     auto balancedend = std::chrono::high_resolution_clock::now();
     
     balancedmean += std::chrono::duration_cast<std::chrono::nanoseconds>(balancedend-balancedstart).count();
    }
    
    outfile_balanced << "\n" << i << "\t" << balancedmean/(i/n_measures);



    double mapmean{0};
    
    for(unsigned int j = 1; j <= i/n_measures; ++j){
      
      auto mapstart = std::chrono::high_resolution_clock::now();
        
        for( unsigned int k = (j-1)*n_measures; k<j*n_measures; ++k){
          
          map.find(values[k]);
        }
     
     auto mapend = std::chrono::high_resolution_clock::now();
     
     mapmean += std::chrono::duration_cast<std::chrono::nanoseconds>(mapend-mapstart).count();
    }
    
    outfile_map<< "\n" << i << "\t" << mapmean/(i/n_measures);

    outfile_tree << std::endl;
    outfile_balanced << std::endl;
    outfile_map << std::endl;

  }
  
  outfile_tree.close();
  outfile_balanced.close();
  outfile_map.close();

}
