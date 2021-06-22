#ifndef bst_hpp
#define bst_hpp

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <iterator>
#include<sstream>

template<typename key_type, typename value_type, typename comparison_type = std::less<key_type> >
class bst{
  
  struct node;
  template<typename T>
  class _iterator;
  
  public:
  using pair_type = typename std::pair<const key_type, value_type>;
  using iterator = _iterator<pair_type>;
  using const_iterator = _iterator<const pair_type>;
  
  private:
  
  comparison_type op;
  
  std::unique_ptr<node> root; // pointer to the root node
  
  void _copy(std::unique_ptr<node>& n){
    
    insert(n.get() -> pair);	    // we insert the value-key pair for the node passed in the copy tree,
				    // creating a new node inside it
    if( n.get()->left ){            // if the passed node has a left child we need to copy it
    
      _copy(n.get() -> left);       // recursive call to this function
    }
    if( n.get()->right ){           // if the passed node has a right child we need to copy it

      _copy(n.get() -> right);      // recursive call
    }

    return;			    // once we have that the node has no more children we have
				    // finished to copy
  }
 

  template<typename O>
  std::pair<iterator, bool> _insert(O&& x){

  auto tmp = root.get();

  while(tmp){     //while tmp != nullptr

    if(op(x.first, tmp -> pair.first)){

      if(tmp -> left){

        tmp = tmp->left.get();

      }else{

        tmp -> left.reset(new node{tmp, std::forward<O>(x)});
        return std::make_pair<iterator, bool>(iterator{tmp}, true);
      }

    }else if( op( tmp -> pair.first, x.first)){

      if(tmp -> right){

        tmp = tmp->right.get();

      }else{

        tmp -> right.reset(new node{tmp, std::forward<O>(x)});
        return std::make_pair<iterator, bool>(iterator{tmp}, true);
      }

    }else{
      
      return std::make_pair<iterator, bool>(iterator{tmp}, false);
    }
  }
  
    //the tree is empty
    root.reset(new node{nullptr, std::forward<O>(x)});
    return std::make_pair<iterator, bool>(iterator{tmp}, true);
  }



  node* _begin() const {

    if(!root){ return nullptr; }  // if the tree is empty (root = nullptr) we return nullptr

    auto tmp = root.get();        
    while( tmp -> left ){         // we keep going to the left until we find a node that has 
                                  // no left child
      tmp = tmp-> left.get();
    }

    return tmp;
  }



  node* _find(const key_type& x) const{

    auto tmp = root.get();

    while(tmp){                         // until tmp is != nullptr

      if(op(x, tmp->pair.first)){       // if the searched key is smaller than the root key
				      // according to the comparison type
        tmp = tmp->left.get();

      }else if(op(tmp->pair.first, x)){ // if the searched key is greater than the root key
      				      // according to the comparison type
        tmp = tmp->right.get();

      }else{
    
        return tmp;
      }
    }
    // the tree is empty or the key doesn't exist, so we return end (which is nullptr)
    return nullptr;
  }



  void _sub_balance( std::vector<pair_type> vec, int a, int b ){

    // return condition to end recursive calls
    if(b < a){ return; }

    int mid{(b+a)/2};		// find mid index
  
    insert(vec[mid]);		// insert the corresponding pair in the vector

    // recursively call the function
    _sub_balance(vec, a, mid-1);
    _sub_balance(vec, mid+1, b);
  
    return;
  }




  public:
   
  // empty ctor
  bst(): op{}, root{nullptr} {}

  // empty ctor but we specify the comparison 
  explicit bst (comparison_type comp): op{comp}, root{nullptr} {}
  
  
  // copy semantics
  
  // copy ctor, we want to perform a deep copy of the tree
  explicit bst(const bst& x): op{x.op}, root{std::unique_ptr<node>(new node(nullptr, x.root.get()->pair))} {

    if( x.root.get()->left ){             // if the root of the copied tree has a left child we need to copy it
    
      _copy(x.root.get() -> left);      // we implement a private function to copy the left subtree
    }
    if( x.root.get()->right ){		  // if the root of the copied tree has a right child we need to copy it

      _copy(x.root.get() -> right);
    }
    
    // std::cout << "copy constructor" << std::endl;
  }

  // copy assignment
  bst& operator=(const bst& x){

    this->clear();
    
    this->insert(x.root.get()->pair);
    
    if( x.root.get() -> left){
      
      _copy(x.root.get() -> left);
    }
    
    if( x.root.get() -> right){
      
      _copy(x.root.get() -> right);
   }
   
   // std::cout << "copy assignment" << std::endl;  
   return *this;
  }

  // move semantics
  
  // move ctor

  bst(bst&&) = default;

  // manual implementation
  //
  // bst(bst&& x): op{std::move(x.op)}, root{std::move(x.root)}{
  //        
  //   x.root.reset(nullptr);
  //
  //   std::cout << "move ctor" << std::endl;
  // }

  // move assignment

  bst& operator=(bst&&) = default;
  
  // manual implementation
  //
  // bst& operator=(bst&& x){
  //
  //  op = std::move(x.op);
  //  
  //  root = std::move(x.root);
  //   
  //  x.root.reset(nullptr);
  //
  //  std::cout << "move assignment" << std::endl;
  //
  //  return *this;
  // }


  // insert
  std::pair<iterator, bool> insert(const pair_type& x){ return _insert(x); }
  std::pair<iterator, bool> insert(pair_type&& x){ return _insert(std::move(x)); }

  
  // emplace
  template< class... Types >
  std::pair<iterator,bool> emplace(Types&&... args){

    return insert(pair_type{std::forward<Types>(args)...});
  }

  // clear
  // Clear the content of the tree
  // The reset function of std::unique_ptr destroys the object currently managed
  // by the unique ptr and takes ownership, if we call it with nullptr the unique_ptr
  // becomes empty, so if we call release(nullptr) to the root the destructor of
  // the root gets called, so all its elements are destroyed, including the pointers
  // to the other nodes, triggering the cascade destruction of the all the tree

  void clear() noexcept{
    root.reset();
  }

  // Begin
  // Return an iterator to the left-most node, implemented through 
  // a private function _begin()

  iterator begin() noexcept{ return iterator{_begin()}; }
  const_iterator begin() const noexcept{ return const_iterator{_begin()}; }
  const_iterator cbegin() const noexcept{ return const_iterator{_begin()}; }

  // End
  // Return an iterator to one-past the last element,
  // which is nullptr

  iterator end() noexcept { return iterator{nullptr}; }
  const_iterator end() const noexcept{ return const_iterator{nullptr}; }
  const_iterator cend() const noexcept{ return const_iterator{nullptr}; }

  // Find
  // Find a given key. If the key is present, returns an iterator to the proper
  // node, end() otherwise. Implemented through a private function _find()

  iterator find(const key_type& x){ return iterator{_find(x)}; }
  const_iterator find(const key_type& x) const{ return const_iterator{_find(x)}; }
  
  // Balance
  // Simple implementation to balance the tree

  void balance(){

    std::vector<pair_type> vec{};      // empty vector to store the key-value pairs
    
    for(auto& i : *this){        // ranged for loop
  
      vec.push_back(i);		       // we copy all the pairs inside the vector
    }

    this->clear();		       // we call the function clear to erase the tree
                                       // in order to replace it with its balanced version

    _sub_balance(vec, 0, vec.size()-1);  // we delegate the balancing process to a private function
  }

  // Subscripting Operator
  // Returns a reference to the value that is mapped to a key equivalent to x,
  // performing an insertion if such key does not already exist.

  value_type& operator[](const key_type& x){
  
    return emplace(x, value_type()).first->second;
  }

  value_type& operator[](key_type&& x){

    return emplace(std::move(x), value_type()).first->second;
  }
  
  // Put to operator
  friend
  std::ostream& operator<<(std::ostream& os, const bst& x){
  
  os << "K\t" << "V\n";
  
    for(const auto& i : x){

      os << i.first  << "\t" << i.second << "\n";
    }
  
  return os;
  }
  
  // Erase
  void erase(const key_type& x){

    auto deleted_iterator = find(x);  // find node to delete, return iterator

    auto deleted_node = deleted_iterator.current; // access the node inside the iterator
    
    // if the tree is empty we return

    if(!deleted_node){ return;}

    // if we are deleting the root

    if(deleted_node == root.get()){      

      // if the root has no children we simply delete it
      if( (!deleted_node->left) && (!deleted_node->right)){
        root.reset(nullptr);

      }else if( (!deleted_node->left) && (deleted_node->right) ){
       
      // if the root only has a right child we make the child the new root
        
        deleted_node->right->parent = nullptr;
        root.reset( deleted_node->right.release());

      }else if( (deleted_node->left) && (!deleted_node->right) ){
       
      // if the root only has a left child we make the child the new root
        deleted_node -> left -> parent = nullptr;
        root.reset( deleted_node->left.release());

      }else{
	 
      // if the root has both children we need to find its successor in terms
      // of keys, which will not have a left child for sure, and replace it
      // with the deleted node, moreover if the successor has a right child 
      // we need replace the successor with it
        
	auto successor = (++deleted_iterator).current;  // find successor

        // we create a new node to store the newly assigned root
	auto new_root = std::unique_ptr<node>(new node(nullptr, successor->pair));
	
        // make left child of new root = left child of deleted and release for deleted
	new_root.get()->left.reset(deleted_node->left.release()); 
	
        // make left child parent = to new root
	new_root.get()->left.get()->parent = new_root.get();

	// for the right child we need to handle the case in which the successor is the 
	// right child of the deleted
	if( deleted_node->right.get() == successor ){

	std::cout << "check 5" << std::endl;

	  // the right child of root becomes the right child of the successor
	  new_root.get()->right.reset(successor->right.release());
	  // set parent of right child to root
          new_root.get()->right.get()->parent = new_root.get();

	}else{

	  std::cout << "check 6" << std::endl;

	  // make right child of new root = right child of deleted and release for deleted
	  new_root.get()->right.reset(deleted_node->right.release());

	std::cout << "check 7" << std::endl;

	  // make right parent = to root
	  new_root.get()->right.get()->parent = new_root.get();

std::cout << "check 8" << std::endl;

	  // we need to handle the case in which successor has a right child
	  if( successor->right ){

std::cout << "check 10" << std::endl;          

	    // make parent of right child of successor equal to successor parent
	    successor->right->parent = successor->parent;
	  
	    // make right child of successor, left child of successor's parent
	    successor->parent->left.reset(successor->right.release());

	  }else{

std::cout << "check 11" << std::endl;	    

	    // reset successor's parent left child
	    successor->parent->left.reset();
          }
        }
	root.reset(new_root.release());
      }
     return;
    }
  }

  // print the tree to visualize each node and its children
  
  void print(){
    
    auto i = cbegin();
    auto stop = cend();

    for( ; i != stop; ++i){

      std::cout << "\nK\t" << "V\n";
      std::cout << (i.current)->pair.first << "\t" << (i.current)->pair.second << "\n";

      if( (i.current)->left ){
        std::cout << "left: k = " << (i.current)->left->pair.first << " v = " << (i.current)->left->pair.second << std::endl;
      }
      if( (i.current)->right ){
        std::cout << "right: k = " << (i.current)->right->pair.first << " v = " << (i.current)->right->pair.second << std::endl;
      }
    }
  }




 
};

#include "node.hpp"
#include "iterator.hpp"



#endif
