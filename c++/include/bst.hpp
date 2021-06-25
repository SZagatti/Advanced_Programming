#ifndef bst_hpp
#define bst_hpp

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <iterator>
#include<sstream>

// ============================== BST CLASS ===============================
// 
// This class represents the concept of a binary search tree, it is 
// templated on the type of the key, the type of the value and the
// comparison operator, which has a default value.


template<typename key_type, typename value_type, typename comparison_type = std::less<key_type> >
class bst{
  
  struct node;			// structure of a node inside the tree (see node.hpp)
  template<typename T>		// class iterator (see iterator.hpp)
  class _iterator;
  
  public:
  using pair_type = typename std::pair<const key_type, value_type>;
  using iterator = _iterator<pair_type>;
  using const_iterator = _iterator<const pair_type>;
  
  private:
  
  comparison_type op;		    // comparison operator
  
  std::unique_ptr<node> root;       // pointer to the root node
  
  //============================== _COPY ===============================
  //
  // A private auxiliary function used to recursively copy a tree by 
  // performing a deep copy of the nodes.
  
  void _copy(std::unique_ptr<node>& n){
    
    insert(n.get() -> pair);	    // insert the value-key pair for the node passed in the
                                    // copy tree, creating a new node inside it

    if( n.get()->left ){            // if the passed node has a left child copy it
    
      _copy(n.get() -> left);       // recursive call to this function
    }
    if( n.get()->right ){           // if the passed node has a right child copy it

      _copy(n.get() -> right);      // recursive call
    }

    return;			    // once we have that the node has no more children we have
				    // finished to copy
  }
 
  //============================= _INSERT ==============================
  //
  // A private auxiliary function that performs insertion of a new node
  // in the tree, given a key-value pair. It has been introduced to 
  // exploit forwarding reference, avoiding code duplication.
  
  template<typename O>
  std::pair<iterator, bool> _insert(O&& x){

  auto tmp = root.get();

  while(tmp){     			   		// while tmp != nullptr					   

    if(op(x.first, tmp -> pair.first)){    		// if the inserted key is smaller than the root key
		                                        // according to the comparison type

      if(tmp -> left){			   		// if there is a left child

        tmp = tmp->left.get();		   		// go down on the left

      }else{				   		// the left child is not present

        // create a new node initialized with the given key-value pair
        // and return a pair iterator_to_the_node - true

        tmp -> left.reset(new node{tmp, std::forward<O>(x)});
        return std::make_pair<iterator, bool>(iterator{tmp}, true);
      }

    }else if( op( tmp -> pair.first, x.first)){		// if the inserted key is greater than the root key
                                                        // according to the comparison type

      if(tmp -> right){					// if there is a right child

        tmp = tmp->right.get();				// go down on the right

      }else{						// the right child is not present

        // create a new node initialized with the given key-value pair
        // and return a pair iterator_to_the_node - true

        tmp -> right.reset(new node{tmp, std::forward<O>(x)});
        return std::make_pair<iterator, bool>(iterator{tmp}, true);
      }

    }else{						

      // in case the key is already present return a pair iterator_to_the_node_false
      
      return std::make_pair<iterator, bool>(iterator{tmp}, false);
    }
  }
  
   // in case tree is empty create a node with the given key-value pair, set it as the root
   // and return a pair iterator_to_the_node - true

    root.reset(new node{nullptr, std::forward<O>(x)});
    return std::make_pair<iterator, bool>(iterator{tmp}, true);
  }

  //============================= _BEGIN ===============================
  //
  // A private auxiliary function that finds the leftmost node, so the
  // one with the smallest key and returns a raw pointer to it.

  node* _begin() const noexcept{

    if(!root){ return nullptr; }  	// if the tree is empty (root = nullptr) we return nullptr

    auto tmp = root.get();        	

    while( tmp -> left ){         	// keep going to the left until a node that has no left
                                  	// child is found and then return it

      tmp = tmp-> left.get();
    }

    return tmp;
  }

  //============================== _FIND ===============================
  //
  // A private auxiliary function that finds a node given its key and 
  // returns a raw pointer to it.

  node* _find(const key_type& x) const noexcept{

    auto tmp = root.get();

    while(tmp){                         // until tmp is != nullptr

      if(op(x, tmp->pair.first)){       // if the searched key is smaller than the root key
				        // according to the comparison type

        tmp = tmp->left.get();		// go down on the left

      }else if(op(tmp->pair.first, x)){ // if the searched key is greater than the root key
      				        // according to the comparison type

        tmp = tmp->right.get();		// go down on the right

      }else{				
    
        return tmp;			// the key doesn't exist, return end (nullptr)
      }
    }

    return nullptr;			// the tree is empty return end (which is nullptr)
  }

  //========================== _SUB_BALANCE ============================
  //
  // A private auxiliary function that creates a balanced tree given the
  // key-value pairs from a vector, starting from the middle value and
  // recursively calling itself.

  void _sub_balance( std::vector<pair_type> vec, int a, int b ){

    // return condition to end recursive calls
    if(b < a){ return; }

    int mid{(b+a)/2};			// find mid index
  
    insert(vec[mid]);			// insert the corresponding pair in the vector

    // recursively call the function for the two sub-vectors

    _sub_balance(vec, a, mid-1);
    _sub_balance(vec, mid+1, b);
  
    return;
  }


  public:
   
  // ctor for an empty bst

  bst() noexcept: op{}, root{nullptr} {}

  // ctor for an empty bst specifying the comparison operator

  explicit bst(comparison_type comp) noexcept: op{comp}, root{nullptr} {}
  
  
  //========================== COPY SEMANTICS ============================
  
  // COPY CONSTRUCTOR:
  // Given a binary search tree it performs a deep copy of it, creating a
  // new binary search tree.

  explicit bst(const bst& x): op{x.op}, root{std::unique_ptr<node>(new node(nullptr, x.root.get()->pair))} {

    if( x.root.get()->left ){    	// if the root of the copied tree has a left child, it has to be copied
   
      _copy(x.root.get() -> left);      // call to the private function _copy to copy the left subtree
    }

    if( x.root.get()->right ){		// if the root of the copied tree has a right child, it has to be copied

      _copy(x.root.get() -> right);	// call to the private function _copy to copy the right subtree
    } 
  }

  // COPY ASSIGNMENT:
  // Given a binary search tree it performs a deep copy of it, creating a
  // new binary search tree.
  
  bst& operator=(const bst& x){

    this->clear();			// clear the new tree
    
    this->insert(x.root.get()->pair);	// create the root of the new tree with key-value pair equal to the
					// root of the copied tree
    
    if( x.root.get() -> left){		// if the copied tree has a left child
      
      _copy(x.root.get() -> left);	// call to the private function _copy to copy the left subtree
    }
    
    if( x.root.get() -> right){		// if the copied tree has a right child
      
      _copy(x.root.get() -> right);	// call to the private function _copy to copy the right subtree
   } 

   return *this;			// return the new tree
  }


  //========================== MOVE SEMANTICS ============================
  
  // MOVE CONSTRUCTOR
  // Given a binary search tree it moves it, creating a new binary search 
  // tree.

  bst(bst&&) = default;			// compiler generated is ok

  // manual implementation
  //
  // bst(bst&& x): op{std::move(x.op)}, root{std::move(x.root)}{
  //        
  //   x.root.reset(nullptr);
  //
  // }

  // MOVE ASSIGNMENT
  // Given a binary search tree it moves it, creating a new binary search 
  // tree.

  bst& operator=(bst&&) = default;	// compiler generated is ok
  
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


  //============================= INSERT ===============================
  //
  // Given a key-value pair new node is created and inserted in the 
  // correct position in the tree; a pair is returned, where the first
  // element is an iterator to the newly inserted node and the second
  // one is a boolean.
  // If the newly inserted key is not already present the boolean is set
  // to true, the node is created with the correct value and inserted in
  // the correct position.
  // If the newly inserted key is already present the boolean is
  // set to false.

  // l-value
  std::pair<iterator, bool> insert(const pair_type& x){ return _insert(x); }
  
  // r-value
  std::pair<iterator, bool> insert(pair_type&& x){ return _insert(std::move(x)); }

  
  //============================= EMPLACE ==============================
  //
  // Given two arguments a proper key_type, value_type pair is created,
  // then a new node is initialized with this key-value pair and 
  // inserted in the tree in the correct position as done in insert.
  // a pair is returned, where the first
  // element is an iterator to the newly inserted node and the second
  // one is a boolean.
  // If the newly inserted key is not already present the boolean is set
  // to true, the node is created with the correct value and inserted in
  // the correct position.
  // If the newly inserted key is already present the boolean is
  // set to false.

  template< class... Types >
  std::pair<iterator,bool> emplace(Types&&... args){

    return insert(pair_type{std::forward<Types>(args)...});
  }


  // ============================= CLEAR ================================
  // 
  // Clears the content of the tree.
  // The reset function of std::unique_ptr destroys the object currently 
  // managed by the unique ptr and takes ownership, if called  with 
  // nullptr the unique_ptr becomes empty, so by applying release(nullptr) 
  // to the root the destructor of the root gets called and all its 
  // elements are destroyed, including the pointers to the other nodes, 
  // triggering the cascade destruction of the whole tree.

  void clear() noexcept{
    root.reset();
  }


  // ============================= BEGIN ================================
  // 
  // Finds the leftmost node of the tree and returns an iterator to it.
  // It has been implemented through a private function _begin that
  // finds the leftmost node and returns its pointer, from which the
  // proper operator is built.

  iterator begin() noexcept{ return iterator{_begin()}; }
  const_iterator begin() const noexcept{ return const_iterator{_begin()}; }


  // ============================= CBEGIN ===============================
  //
  // Constant version of begin, returning a constant iterator.

  const_iterator cbegin() const noexcept{ return const_iterator{_begin()}; }


  // ============================== END =================================
  // 
  // Returns an iterator to one past the last element (in terms of keys)
  // of the tree, so a pointer to nullptr.

  iterator end() noexcept { return iterator{nullptr}; }
  const_iterator end() const noexcept{ return const_iterator{nullptr}; }


  // ============================= CBEGIN ===============================
  //
  // Constant version of end, returning a constant iterator.

  const_iterator cend() const noexcept{ return const_iterator{nullptr}; }


  // ============================== FIND ================================
  //
  // Finds the node corresponding to a given key inside the tree.
  // If the key is present, returns an iterator to the proper
  // node, otherwise it returns end(). 
  // It has been implemented through a private function _find() that
  // looks for the key inside the tree.

  iterator find(const key_type& x){ return iterator{_find(x)}; }
  const_iterator find(const key_type& x) const{ return const_iterator{_find(x)}; }

  
  // ============================= BALANCE ==============================
  //
  // Simple implementation of balancing a tree. It scans the tree from
  // begin() to end() and fills a vector with all the key-value pairs,
  // then the private function _sub_balance finds the middle index of the
  // vector and inserts the corresponding pair in the tree, then the same 
  // strategy is applied to the subvectors created this way by recursive
  // calls of the private function

  void balance(){

    std::vector<pair_type> vec{};      	// empty vector to store the key-value pairs
    
    for(const auto& i : *this){        	// ranged for loop inside the tree
  
      vec.push_back(i);		       	// copy all the pairs inside the vector
    }

    this->clear();		       	// clear the tree in order to replace it with its balanced version

    _sub_balance(vec, 0, vec.size()-1); // we delegate the balancing process to a private function
  }


  // ====================== SUBSCRIPTING OPERATOR =======================
  //
  // Given a key it returns a reference to the value that is mapped to it,
  // performing an insertion if such key does not already exist.

  // l-value
  value_type& operator[](const key_type& x){
  
    return emplace(x, value_type()).first->second;
  }
  
  // r-value
  value_type& operator[](key_type&& x){

    return emplace(std::move(x), value_type()).first->second;
  }
  
  
  // ========================= PUT TO OPERATOR =========================
  //
  // Prints keys and values of the nodes of the tree from the leftmost 
  // to the rightmost node.
  // In case of using not built-in types as key_type or value_type
  // the put to operator must be defined for them as well.

  friend
  std::ostream& operator<<(std::ostream& os, const bst& x){
  
  os << "Key:\t" << "Value:\n";
  
    for(const auto& i : x){ 		// ranged for loop on the tree

      os << i.first  << "   \t" << i.second << "\n";
    }
  
  return os;
  }
  

  // ============================== ERASE ==============================
  //
  // Given a key it finds the corresponding node and deletes it,
  // re-arranging the tree in a such a way that all the constraints are
  // respected.

  void erase(const key_type& x){

    auto deleted_iterator = find(x);  				// find node to delete, return iterator

    auto deleted_node = deleted_iterator.current; 		// access the node inside the iterator
    
    if(!deleted_node){ return;}					// if the tree is empty return

    if(deleted_node == root.get()){      			// if the root is being deleted

      // if the root has no children simply delete it

      if( (!deleted_node->left) && (!deleted_node->right)){	
        root.reset(nullptr);

      }else if( (!deleted_node->left) && (deleted_node->right) ){
       
      // if the root only has a right child make the child the new root
        
        deleted_node->right->parent = nullptr;
        root.reset( deleted_node->right.release());

      }else if( (deleted_node->left) && (!deleted_node->right) ){
       
      // if the root only has a left child make the child the new root

        deleted_node -> left -> parent = nullptr;
        root.reset( deleted_node->left.release());

      }else{
	 
      // if the root has both children find its successor in terms
      // of keys, which will not have a left child for sure, and replace it
      // with the deleted node, moreover if the successor has a right child 
      // replace the successor with it
        
	auto successor = (++deleted_iterator).current;  // find successor

        // create a new node to store the newly assigned root
	auto new_root = std::unique_ptr<node>(new node(nullptr, successor->pair));
	
        // make left child of new root = left child of deleted and release for deleted
	new_root.get()->left.reset(deleted_node->left.release()); 
	
        // make left child parent = to new root
	new_root.get()->left.get()->parent = new_root.get();

	// for the right child handle the case in which the successor is the 
	// right child of the deleted node
	if( deleted_node->right.get() == successor ){
    
	  // the right child of root becomes the right child of the successor
          new_root.get()->right.reset(successor->right.release());
          
          if( new_root.get()->right.get()){

	    // set parent of right child to root
            new_root.get()->right.get()->parent = new_root.get();
	  }

	}else{

	  // make right child of new root = right child of deleted and release for deleted
	  new_root.get()->right.reset(deleted_node->right.release());

	  // make right parent = to root
	  new_root.get()->right.get()->parent = new_root.get();

	  // handle the case in which successor has a right child
	  if( successor->right ){

	    // make parent of right child of successor equal to successor parent
	    successor->right->parent = successor->parent;
	  
	    // make right child of successor, left child of successor's parent
	    successor->parent->left.reset(successor->right.release());

	  }else{

	    // reset successor's parent left child
	    successor->parent->left.reset();
          }
        }

	root.reset(new_root.release());
      }

     return;
    }
    
    // delete any other node, it will for sure have a parent
    
    auto parent_deleted = deleted_node->parent;  		// parent of the deleted node

    // simplest case: the node to delete is a leaf, so it has no children
    if((!deleted_node->left) && (!deleted_node->right)){
      
      // the deleted node is the left child of its parent
      if( parent_deleted->left.get() == deleted_node ){

	parent_deleted->left.reset();

      // the deleted node is the right child of its parent
      }else if( parent_deleted->right.get() == deleted_node ){ 
        
        parent_deleted->right.reset();
      }

    // 2nd case: the node to delete has a left child
    }else if( (deleted_node->left) && (!deleted_node->right) ){

      // set child's parent to be the parent of node to delete
      deleted_node->left->parent = parent_deleted; 

      // the deleted node is the left child of its parent
      if( parent_deleted->left.get() == deleted_node ){
      
        parent_deleted->left.reset(deleted_node->left.release());
        
      // the deleted node is the right child of its parent
      }else if( parent_deleted->right.get() == deleted_node ){
        
        parent_deleted->right.reset(deleted_node->left.release());
      }

    // 2nd case: the node to delete has a right child
    }else if( (!deleted_node->left) && (deleted_node->right) ){

      // set child's parent to be the parent of node to delete
      deleted_node->right->parent = parent_deleted;
    
      // the deleted node is the left child of its parent
      if( parent_deleted->left.get() == deleted_node ){
    
        parent_deleted->left.reset(deleted_node->right.release());
    
      // the deleted node is the right child of its parent
      }else if( parent_deleted->right.get() == deleted_node ){
     
        parent_deleted->right.reset(deleted_node->right.release());
      }

    // 3rd case: the node to delete has both left and right children
    }else if( (deleted_node->left) && (deleted_node->right) ){
      
      // Find its successor in terms of keys, which will for sure 
      // not have a left child, and replace it with the deleted node

        auto successor = (++deleted_iterator).current;  	// find successor

        // create a new node initialized with the values from the successor
	// of the deleted node
        auto new_node = std::unique_ptr<node>(new node(parent_deleted, successor->pair));

        // make left child of new node = left child of deleted and release for deleted
        new_node.get()->left.reset(deleted_node->left.release());

        // make left child parent = to new node
        new_node.get()->left.get()->parent = new_node.get();

        // for the right child we need to handle the case in which the successor is the 
        // right child of the deleted
        if( deleted_node->right.get() == successor ){
	  
          // the right child of the node becomes the right child of the successor
          new_node.get()->right.reset(successor->right.release());
          
          if(new_node.get()->right.get()){  
	  
	    // set parent of right child to new node
            new_node.get()->right.get()->parent = new_node.get();
          
          }
          if( parent_deleted->left.get() == deleted_node){
            
            parent_deleted->left.reset(new_node.release());

          }else{   

	    parent_deleted->right.reset(new_node.release());
          }

	}else{

          // make right child of new node = right child of deleted and release for deleted
          new_node.get()->right.reset(deleted_node->right.release());

          // make right parent = to new node
          new_node.get()->right.get()->parent = new_node.get();

	  if( parent_deleted->left.get() == deleted_node){
            
            parent_deleted->left.reset(new_node.release());
          
          }else{   

            parent_deleted->right.reset(new_node.release());
          }

          // we need to handle the case in which successor has a right child
          if( successor->right ){

            // make parent of right child of successor equal to successor parent
            successor->right->parent = successor->parent;

            // make right child of successor, left child of successor's parent
            successor->parent->left.reset(successor->right.release());

          }else{

            // reset successor's parent left child
            successor->parent->left.reset();
          }
        }
      }
      // the tree is empty or the key we are deleting is not present
      return;
    } 


  // ============================== PRINT ==============================
  // 
  // Prints more information than the overloading of the put to operator.
  // The tree is scanned from begin() to the end() and for each node
  // the function prints the key-value pair and the key value pairs of
  // the left and right children of the node, if they are present.
  
  void print() noexcept{
    
    auto i = cbegin();
    auto stop = cend();

    for( ; i != stop; ++i){

      std::cout << "\nKey:\t" << "Value:\n";
      std::cout << (i.current)->pair.first << "   \t" << (i.current)->pair.second << "\n";

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
