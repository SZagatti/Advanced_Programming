#ifndef node_hpp
#define node_hpp

template<typename key_type, typename value_type, typename comparison_type>
struct bst<key_type, value_type, comparison_type>::node{

  // pointer to the parent node
  std::unique_ptr<node> parent;
  
  // pointer to the right child
  std::unique_ptr<node> right;

  // pointer to the left child
  std::unique_ptr<node> left;

  // each node stores a key-value pair
  std::pair<const key_type, value_type> pair;

  // ctors
  node() = default; //create an empty node, all pointers are set to nullptr
  
  // ctor with parent and pair (l-value and r-value)
  node(node* p, std::pair<const key_type, value_type>& data) :
    parent{p}, right{nullptr}, left{nullptr}, pair{data}{}

  node(node* p, std::pair<const key_type, value_type>&& data) :
    parent{p}, right{nullptr}, left{nullptr}, pair{data}{}

  // destructor
  ~node() = default;
};

#endif
