#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <iterator>
#include "bst.hpp"

// ============================== TEST ===============================
//
// We perform a series of tests to make sure that all the functions
// implemented in the bst class are working as expected.

int main(){

  // CREATION OF EMPTY BST
  std::cout << "========== EMPTY BINARY SEARCH TREE =========\n";
  std::cout << "We expect an empty output:\n\n";
  
  bst<int, char> tree;
  std::cout << tree << std::endl;
  
  // bst with different comparison operator
  
  std::cout << "Test building an empty tree with a different comparison operator:\n\n";
  bst<int, char, std::greater<int> > gtree;
  std::cout << gtree << std::endl;
  
  // INSERTION 
  
  std::cout << "========== INSERTION ==========\n";
  std::cout << "We expect the following tree:\n";
  std::cout << "     4\n   /  \\ \n  2    6\n / \\  / \\ \n1  3  5  7\n" << std::endl;
  
  // l-value insertion
  tree.insert(std::pair<int, char>(4, 'd'));
  tree.insert(std::pair<int, char>(2, 'b'));
  tree.insert(std::pair<int, char>(6, 'f'));

  // r-value insertion
  std::pair<int, char> a = std::make_pair(1, 'a');
  std::pair<int, char> c = std::make_pair(3, 'c');
  std::pair<int, char> e = std::make_pair(5, 'e');
  std::pair<int, char> g = std::make_pair(7, 'g');
  
  tree.insert(a);
  tree.insert(c);
  tree.insert(e);  
  tree.insert(g);  

  std::cout << "Traversing the tree we obtain:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();

  // insertion with already present key

  std::cout << "\nInsertion of an already present key:";
  auto already_ins = tree.insert(std::pair<int, char>(6, 'z'));

  std::cout << " returned iterator with key " << (already_ins.first)->first;
  std::cout << " and value " << (already_ins.first)->second << ", ";
  std::cout << "flag = " << std::boolalpha << already_ins.second << "." << std::endl;
  
  // EMPLACE

  bst<int, char> tree2;
  std::cout << "\n========== EMPLACE ==========\n";
  std::cout << "We expect the same tree as before.\n";
    
  // l-value insertion
  tree2.emplace(4, 'd');
  tree2.emplace(2.5, 'b'); // implicit conversion
  tree2.emplace(std::pair<int, char>(6, 'f'));

  // r-value insertion
  int a1{1};
  char a2{'a'};
  std::pair<int, char> c1 = std::make_pair(3, 'c');
  std::pair<double, char> e1 = std::make_pair(5.5, 'e'); //implicit conversion
  double g1{7.7};
  char g2{'g'};
  
  tree2.emplace(a1, a2);
  tree2.emplace(c1);
  tree2.emplace(e1);
  tree2.emplace(g1, g2);

  std::cout << "Traversing the tree we obtain:\n";
  std::cout << tree2 << std::endl;;
  std::cout << "Nodes:\n";
  tree2.print();

  std::cout << "\nInsertion of an already present key:";
  auto already_emp = tree2.emplace(6, 'z');

  std::cout << " returned iterator with key " << (already_emp.first)->first;
  std::cout << " and value " << (already_emp.first)->second << ", ";
  std::cout << "flag = " << std::boolalpha << already_emp.second << std::endl;
  
  // TEST TREE WITH GREATER THAN
  std::cout << "\nTesting insertion and visualization of a tree with std::greater<key_type> inserting method:\n\n";
  std::cout << "\nExpected tree:\n";
  std::cout << "     4\n   /  \\ \n  6    2\n / \\  / \\ \n7  5  3  1\n" << std::endl;  

  // l-value insertion
  gtree.insert(std::pair<int, char>(4, 'd'));
  gtree.insert(std::pair<int, char>(2, 'b'));
  gtree.insert(std::pair<int, char>(6, 'f'));

  // r-value insertion
  std::pair<int, char> ag = std::make_pair(1, 'a');
  std::pair<int, char> cg = std::make_pair(3, 'c');
  std::pair<int, char> eg = std::make_pair(5, 'e');
  std::pair<int, char> gg = std::make_pair(7, 'g');

  gtree.insert(ag);
  gtree.insert(cg);
  gtree.insert(eg);
  gtree.insert(gg);
  
  std::cout << "Traversing the tree we obtain:\n";
  std::cout << gtree << std::endl;;
  std::cout << "Nodes:\n";
  gtree.print();

  // CLEAR
  std::cout << "\n========== CLEAR ==========\n";
  std::cout << "We clear the previous tree (we expect empty output)." << std::endl;
  tree2.clear();
  tree2.print();

  // FIND
  std::cout << "\n========== FIND ==========\n";
  std::cout << "We look for a key that we know is present (5):\n";
  
  auto found = tree.find(5);
  
  if( found != tree.end()){ 

    std::cout << "returned key: " << found->first << " returned value: " << found->second << std::endl; 

  }else if( found == tree.end() ){ 
	std::cout << "key not found, I returned end() (nullptr)" << std::endl; 
    
  }else{ std::cout << "unknwn behaviour" << std::endl; }

  std::cout << "We look for a key that we know is not present (10):\n";

  auto notfound = tree.find(10);
   
  if( notfound != tree.end()){ 

    std::cout << "returned key: " << notfound->first << " returned value: " << notfound->second << std::endl;

  }else if( notfound == tree.end() ){ 
        std::cout << "key not found, i returned end() (nullptr)" << std::endl;

  }else{ std::cout << "unknwn behaviour" << std::endl; }

  // SUBSCRIPTING OPERATOR
  std::cout << "\n========== SUBSCRIPTING OPERATOR ==========\n";
  std::cout << "\nAlready present keys (2 and 5, expected outputs 'b' and 'e'):\n";
  
  // l-value:
  std::cout << tree[2] << "\n";
  //r-value:
  int r = 5;
  std::cout << tree[r] << std::endl;

  std::cout << "\nKeys not present (10 and 15), we expect insertions in the tree:\n";
  
  // l-value:
  tree[10];
  // r-value:
  int rr = 15;
  tree[rr];

  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();
  
  // COPY and MOVE SEMANTICS
  std::cout<<"\n========== COPY and MOVE SEMANTICS ==========\n";
  std::cout<<"\nWe test of the following tree:\n";
  std::cout << "     4\n   /  \\ \n  2    6\n / \\  / \\ \n1  3  5  7\n" << std::endl;
  
  tree.clear();
  tree.insert(std::pair<int, char>(4, 'd'));
  tree.insert(std::pair<int, char>(2, 'b'));
  tree.insert(std::pair<int, char>(6, 'f'));
  tree.insert(std::pair<int, char>(1, 'a'));
  tree.insert(std::pair<int, char>(3, 'c'));
  tree.insert(std::pair<int, char>(5, 'e'));
  tree.insert(std::pair<int, char>(7, 'g')); 

  std::cout<<"\nOriginal tree:\n";
  
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();
  

  std::cout<<"\nTree obtained with Copy Constructor:\n";

  bst<int, char> tree3{tree};

  std::cout << tree3 << std::endl;
  std::cout << "Nodes:\n";
  tree3.print();

  std::cout<<"\nTree obtained with Copy Assignment:\n";
  
  bst<int, char> tree4;
  tree4 = tree;

  std::cout << tree4 << std::endl;
  std::cout << "Nodes:\n";
  tree4.print();

  std::cout<<"\nTree obtained with Move Constructor:\n";

  bst<int, char> tree5{std::move(tree3)};

  std::cout << tree5 << std::endl;
  std::cout << "Nodes:\n";
  tree5.print();
  
  std::cout<<"\nThe tree from which we have moved should be empty:\n";
  std::cout << tree3 << std::endl;
  std::cout << "Nodes:\n";
  tree3.print();

  std::cout<<"\nTree obtained with Move Assignment:\n";
  
  bst<int, char> tree6;
  tree6 = std::move(tree4);
   
  std::cout << tree6 << std::endl;
  std::cout << "Nodes:\n";
  tree6.print();
   
  std::cout<<"\nThe tree from which we have moved should be empty:\n";
  std::cout << tree4 << std::endl;
  std::cout << "Nodes:\n";
  tree4.print();
 
  // ERASE
  std::cout<<"\n========== ERASE ==========\n";
  std::cout << "We test on the following tree:\n";
  std::cout << "     4\n   /  \\ \n  2    6\n / \\  / \\ \n1  3  5  7\n" << std::endl;

  std::cout << "We erase node 5, which is a leaf.";
  tree.erase(5);
  
  std::cout<<"\nObtained tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();
  
  std::cout << "\nWe erase node 6, which is not a leaf, nor the root and has a right child.";  
  tree.erase(6);
  
  std::cout<<"\nObtained tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();
  
  std::cout << "\nWe erase node 2 which is not a leaf, nor the root and has both a right and a left child";
  tree.erase(2);

  std::cout<<"\nObtained tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();
  
  std::cout << "\nWe erase node 3 which is not a leaf, nor the root and has a left child";
  tree.erase(3);
  
  std::cout<<"\nObtained tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();

  std::cout << "\nWe erase node 1 which is a leaf and left child of the root";
  tree.erase(1);
      
  std::cout<<"\nObtained tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();
   
  std::cout << "\nWe erase node 7 which is a leaf and right child of the root";
  tree.erase(7);
          
  std::cout<<"\nObtained tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();

  std::cout << "\nWe erase node 4 which is a root";
  tree.erase(4);
          
  std::cout<<"\nObtained tree (should be empty):\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();
  
  std::cout<<"\nWe rebuild a tree to test erasing the root (root + left child + right child is enough)";
  
  tree.insert(std::pair<int, char>(4, 'd'));
  tree.insert(std::pair<int, char>(2, 'b'));
  tree.insert(std::pair<int, char>(6, 'f'));
  
  std::cout<<"\nWe erase the root";
  tree.erase(4);  

  std::cout<<"\nObtained Tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();
  
  std::cout<<"\nWe erase the root again";
  tree.erase(6);  
 
  std::cout<<"\nObtained Tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();

  std::cout<<"\nWe build a tree to test erasing the root in the case its successor is not the right child";
  tree.clear();
  
  tree.insert(std::pair<int, char>(8, 'h'));
  tree.insert(std::pair<int, char>(10, 'l'));
  tree.insert(std::pair<int, char>(9, 'i'));
  tree.insert(std::pair<int, char>(3, 'c'));
  tree.insert(std::pair<int, char>(6, 'f'));
  tree.insert(std::pair<int, char>(4, 'd'));
  tree.insert(std::pair<int, char>(1, 'a'));
  tree.insert(std::pair<int, char>(14, 'p'));
  tree.insert(std::pair<int, char>(13, 'o'));
  tree.insert(std::pair<int, char>(7, 'g'));
  
  std::cout<<"\nOriginal Tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();
  
  tree.erase(8);
  std::cout<<"\nObtained Tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();

  tree.clear();

  // BALANCE

  std::cout<<"\n========== BALANCE ==========\n";
  std::cout<<"\nWe build the tree from the exam assignment to test balancing the tree, the tree is the following:\n";

  tree.insert(std::pair<int, char>(8, 'h'));
  tree.insert(std::pair<int, char>(10, 'l'));
  tree.insert(std::pair<int, char>(3, 'c'));
  tree.insert(std::pair<int, char>(6, 'f'));
  tree.insert(std::pair<int, char>(4, 'd'));
  tree.insert(std::pair<int, char>(1, 'a'));
  tree.insert(std::pair<int, char>(14, 'p'));
  tree.insert(std::pair<int, char>(13, 'o'));
  tree.insert(std::pair<int, char>(7, 'g'));

  std::cout<<"     8\n   /  \\ \n  3    10\n / \\    \\ \n1   6    14\n   / \\  /\n  4   7 13" << std::endl;

  std::cout<<"\nOriginal Tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();

  std::cout<<"\nUsing the implemented method the balanced tree shpuld be:\n";
  std::cout<<"     7\n   /  \\ \n  3    10\n / \\   / \\ \n1   4 8  13\n     \\    \\ \n      6   14" << std::endl;

  tree.balance();  
  
  std::cout<<"\nBalanced Tree:\n";
  std::cout << tree << std::endl;
  std::cout << "Nodes:\n";
  tree.print();

  return 0;
}
