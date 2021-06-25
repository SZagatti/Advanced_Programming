#ifndef iterator_hpp
#define iterator_hpp

// ============================== ITERATOR ===============================
//
// Class that implements the iterator for the binary search tree

template<typename key_type, typename value_type, typename comparison_type>
template<typename T>
class bst<key_type, value_type, comparison_type>::_iterator{

  node* current;		// node referred to by the iterator

  // standard members of an iterator
  public:
  using val_type = T;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using reference = val_type&;
  using pointer = val_type*;
  
  // de-reference operator
  reference operator*() const noexcept { return current->pair; }

  // arrow operator
  pointer operator->() const noexcept { return &(*(*this)); }
  
  // pre increment  operator
  _iterator& operator++() noexcept{
    
    if(!current){			// if current is nullptr return current

      return *this;
    
    }else if(current->right){ 		// if current has a right child jump to it
    
      current = current ->right.get();

      while(current -> left){ 		// until we have a left child jump to it

        current = current -> left.get();
      }

    }else{                    		// if current has not a right child go up
      
      node* up = current->parent;
      while(up != nullptr && current == up->right.get()){ // go up until reaching a nullptr, stop if right child
                                  
        current = up;
        up = current->parent;
      }

    current = up;
    }
    
    return *this;
  }

  // post increment
  _iterator &operator++(int) noexcept {
    
    auto tmp{*this};
    ++(*this);
    return tmp;
  }


  // construct an iterator given a pointer to a node
  explicit _iterator(node* n): current{n} {}
  
  // Equality operator
  friend
  bool operator==(const _iterator& a, const _iterator& b){
    
    return a.current == b.current;
  }
  
  // Inequality operator
  friend
  bool operator!=(const _iterator& a, const _iterator& b){

    return !(a==b);
  }
  

  // bst has to be a friend class in order to be able to access the private
  // members of the iterators
  friend class bst;
};

#endif
