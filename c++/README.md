# Advanced Programming - Binary Search Tree

Implementation of a Binary Search Tree data structure in C++ for the Advanced Programming exam of the DSSC master's degree, University of Trieste.

Author: Sebastiano Zagatti ( sebastiano.zagatti@gmail.com )

## Repository Structure

* `include` contains:  `node.hpp`, implementation of a class node of the binary search tree; `iterator.hpp`, implementation of the iterator class;  `bst.hpp`, implementation of a binary search tree and its member function.
* `src` contains; `test.cpp`, a C++ script to test the functions of the binary search tree class; `benchmark.cpp` a C++ script to benchmark the binary search tree class with respect to `std::map`; `benchmark_graphs.R` a simple R script to produce the plots for the benchmark; `benchmark_results` a folder containing the results of the benchmark.

## How to Compile and Run

The provided `Makefile` is used to automatically compile the whole project, moreover it is also possible to compile only part of it using the following commands:

* `make test` generates an executable `test.x` in which all the functions implemented in the binary search tree class are tested.
* `make benchmark` generates an executable `benchmark.x` that performs the test for benchmarking both the unordered and ordered binary search trees with respect to `std::map`.

Both executables can be generated with the `make` command and in order to remove them the `make clean` command can be used.

## Report

The aim of this project is to implement a template binary search tree (BST) in C++. A BST is a hierarchical data structure in which each node stores a key-value pair and can have at most two children: left and right. The tree is ordered according to the keys and allows for insertion and removal of nodes, balancing of the tree and look-up of a key.

### Structure of the code

Three header files have been implemented and can be found in the `include` directory:

* `node.hpp` is the implementation of a node in the binary search tree and has four members: a raw pointer `parent` to the parent node, two unique pointers to the children (`left` and `right`) and a `std::pair` to store the key-value pairs; moreover, it also has a constructor to create an empty node and copy and move constructors.
* `iterator.hpp` is the implementation of a forward iterator for the BST and has a member `current` which is a raw pointer to node. It also has various operator overloadings: **dereference operator** `operator*` to access the key-value pair, **arrow operator** `operator->` to access the members of the node, **pre-** and **post-increment** operators to traverse the tree and **equality** and **inequality** operators; moreover, a constructor has been defined in order to create an iterator given a pointer to a node.
* `bst.hpp` is the implementation of the binary search tree, it is templated on the key type, the value type and the comparison operator, which is set by default to `std::less` for the key type. Inside this class a pointer to the root node of the tree has been defined as a member, as well as several private auxiliary members, to help with the implementation of the public members, default, copy and move constructors, operator overloadings and public methods.

Two scripts have been created and can be found in the `src` directory:

* `test.cpp` is a script in which all the implemented methods and copy and move semantics have been tested in order to verify their correct behaviour.
* `benchmark.cpp` is a script to test and compare the performances of the unbalanced and balanced implemented BST with respect to `std::map`.

Inside the `src` directory it is also possible to find a directory `benchmark_results` which storest the results of the benchmark and an R script to produce the graphs of those results.

### Member Functions

#### Insert

Given a key-value pair, a new node is created and inserted in the correct position in the tree; a pair is returned, where the first element is an iterator to the newly inserted node and the second one is a boolean. If the newly inserted key is not already present the boolean is set to true, the node is created with the correct value and inserted in the correct position. If the newly inserted key is already present the boolean is set to false.

#### Emplace

Given two arguments a proper key_type, value_type pair is created, then a new node is initialized with this key-value pair and inserted in the tree in the correct position using the insert method.

#### Clear

Clears the content of the tree by resetting the root of the tree.

#### Begin and End

Begin finds the leftmost node of the tree and returns an iterator to it. It has been implemented through a private function `_begin` that finds the leftmost node and returns its pointer, from which the proper operator is built.

End returns an iterator to one past the last element, which is `nullptr`.

#### Find

It finds the node corresponding to a given key inside the tree. If the key is present, returns an iterator to the proper node, otherwise it returns `end()`. It has been implemented through a private function `_find()` that looks for the key inside the tree and returns a pointer to the corresponding node, from which an iterator is created.

#### Balance

It scans the tree from `begin()` to `end()` and fills a vector with all the key-value pairs, then the tree is cleared and the private function `_sub_balance` finds the middle index of the vector, inserting the corresponding pair in the tree. The same strategy is applied to the subvectors created this way by recursive calls of the private function.

#### Subsripting Operator `[ ]`

Overloading of the operator `[ ]`: given a key, it returns a reference to the value that is mapped to it, performing an insertion if such key is not already present.

#### Put-to Operator `<<`

Overloading of the operator `<<`: it prints keys and values of the nodes of the tree from the leftmost to the rightmost nodes.

#### Erase

Given a key, it finds the corresponding node and deletes it, re-arranging the tree in a such a way that all the constraints are respected. It considers whether the node we are trying to delete is the root or not.

## Benchmark

The purpose of this benchmark is to compare the performance of the proposed implementation with the one from `std::map`; in particular, the comparison is carried out on the `find()` method, considering both the unbalanced and the balanced version of the implemented BST.

Each data structure involved in the benchmark has been filled with a number of randomised integer key - integer value pairs, ranging from 1000 to 100000 with an increment of 1000 at each step. For each iteration a vector has been filled with integer consecutive numbers from 1 to the number of pairs in that step, then the vector has been randomized and the pairs have been inserted in the different structures. Subsequently, the vector has been randomized again and divided in chunks of 50, then for each chunk the time to find all the 50 values has been considered as a measure of performance, therefore obtaining a number of measures equal to the number of nodes inserted in each step divided by 50. In this way from all these measures a mean value has been obtained for each step. The results of the benchmark are displayed in the following graphs, where the script and the data structures have been compiled with different levels of compiler optimisation.

![title](/plots/no_opt.png)

![title](/plots/O1.png)

![title](/plots/O2.png)

![title](/plots/O3.png)

In general, it is possible to observe that in every case the balanced tree has better performance than the unbalanced version, in accordance with the expectations. Different considerations can be made for `std::map` which behaves in a different way compared to the expectations. It is possible to notice that `std::map` has a worse performance than both balanced and unbalanced versions of the tree in the case of no optimization and an in between performance in the case of one degree of optimization. Moreover, for the other two cases `std::map` behaves as expected, having a much better performance than the other two data structures. This behaviour could be explained by considering that the simpler implementation of the proposed data structure could spawn an executable which is more performant than the deeper and more sophisticated implementation of `std::map` when considering lower levels of optimization; then once the optimization is present `std::map` gains much more performance from the compiler optimization.
