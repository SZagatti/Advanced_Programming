#ifndef node_hpp
#define node_hpp

template<typename N, typename TT>          // class iterator (see iterator.hpp)
class _iterator;

template<typename key_type, typename value_type, typename comparison_type>
class bst;


// ============================== NODE ===============================
//
// Structure encoding the concept of a node in a binary search tree.

template<typename T>
class node{

  // pointer to the parent node
  node* parent;
  
  // pointer to the right child
  std::unique_ptr<node<T>> right;

  // pointer to the left child
  std::unique_ptr<node<T>> left;

  // each node stores a key-value pair
  T pair;

  // ctor
  node() noexcept: parent{nullptr}, left{nullptr}, right{nullptr}, pair{} {} //create an empty node, all pointers are set to nullptr

  // copy ctor with parent and pair
  node(node<T>* p, const T& data):
    parent{p}, right{nullptr}, left{nullptr}, pair{data}{}
  
  // move ctor with parent and pair
  node(node<T>* p, T&& data):
    parent{p}, right{nullptr}, left{nullptr}, pair{std::move(data)}{}

  template<typename N, typename TT>
  friend class _iterator;

  template<typename key_type, typename value_type, typename comparison_type>
  friend class bst;
};

#endif
