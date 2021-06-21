#ifndef bst_hpp
#define bst_hpp

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <iterator>

template<typename key_type, typename value_type, typename comparison_type = std::less<key_type> >
class bst{
  
  struct node;
  template<typename T>
  class _iterator;
  
  public:
  using pair_type = typename std::pair<const key_type, value_type>;
  using iterator = _iterator<pair_type>;
  using const_iterator = _iterator<const pair_type>;
  comparison_type op;
  
  private:

  std::unique_ptr<node> root; // pointer to the root node
  
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
  // the tree is empty or the key doesn't exist, so we return end (which is nullptr)
  return nullptr;
}



void _sub_balance( std::vector<pair_type> vec, unsigned int a, unsigned int b ){

  // return condition to end recursive calls
  if(b < a){ return; }

  int mid{(b+a)/2};		// find mid index

  this->insert(vec[mid]);		// insert the corresponding pair in the vector

  // recursively call the function
  _sub_balance(vec, 0, mid-1);
  _sub_balance(vec, mid+1, b);
  
  return;
}




  public:
  
  // empty ctor
  bst (): op{}, root{nullptr} {}

  // empty ctor but we specify the comparison 
  explicit bst (comparison_type comp): op{comp}, root{nullptr} {}

  // insert

  std::pair<iterator, bool> insert(const pair_type& x){ return _insert(x); }
  std::pair<iterator, bool> insert(pair_type&& x){ return _insert(std::move(x)); }

  
  // emplace
  template< class... Types >
  std::pair<iterator,bool> emplace(Types&&... args){

    return insert(pair_type{std::forward<Types>(args)...});
  }

  // clear
  void clear();

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
    
    for(const auto& i : *this){        // ranged for loop
      
      vec.push_back(i);		       // we copy all the pairs inside the vector
    }

    this->clear();		       // we call the function clear to erase the tree
                                       // in order to replace it with its balanced version

    unsigned int mid{vec.size()/2};    // fin the mid index of the vector

    this->insert(vec[mid]);	       // the value corresponding to the mid position will
				       // be the root

    // now we need to consider the sub vectors, we delegate to another private function
    
    _sub_balance(v, 0, mid-1);
    _sub_balance(v, mid+1, vec.size());
  }

  // Subscripting Operator
  // Returns a reference to the value that is mapped to a key equivalent to x,
  // performing an insertion if such key does not already exist.

  value_type& operator[](const key_type& x){
  
    return insert()
  }
  value_type& operator[](key_type&& x);
  
  // Put to operator
  friend
  std::ostream& operator<<(std::ostream& os, const bst& x);
  
  // copy and move
  
  // Erase
  void erase(const key_type& x);
 
};

#include "node.hpp"
#include "iterator.hpp"



#endif











