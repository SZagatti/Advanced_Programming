#ifndef iterator_hpp
#define iterator_hpp

template<typename key_type, typename value_type, typename comparison_type>
template<typename T>
class bst<key_type, value_type, comparison_type>::_iterator{

  node* current;

  public:
  using val_type = T;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using reference = val_type&;
  using pointer = val_type*;

  reference operator*() const noexcept { return current->pair; }
  pointer operator->() const noexcept { return &(*(*this)); }
  
  // pre increment  
  _iterator& operator++() {
    
    // if current is nullptr we return current
    if(!current){

      return *this;
    
    }else if(current->right){ // if current has a right child we jump to it
    
      current = current ->right.get();

      while(current -> left){ // until we have a left child we jump to it

        current = current -> left.get();
      }

    }else{                    // if current has not a right child we need to go up
      
      node* up = current->parent;
      while(up != nullptr && current == up->right.get()){ // we go up until we reach a nullptr or we are
                                                          // not a right child anymore
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

  // constructor given the node
  explicit _iterator(node* n): current{n} {}

  friend
  bool operator==(const _iterator& a, const _iterator& b){
    
    return a.current == b.current;
  }

  friend
  bool operator!=(const _iterator& a, const _iterator& b){

    return !(a==b);
  }
  
  friend class bst;
};

#endif
