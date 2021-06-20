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



node* _find() const{

  auto tmp = root.get();




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

  iterator find(const key_type& x){ return iterator{_find()}; }
  const_iterator find(const key_type& x) const{ return iterator{_find()}; }
  
  // Balance
  void balance();

  // Subscripting Operator
  value_type& operator[](const key_type& x);
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











