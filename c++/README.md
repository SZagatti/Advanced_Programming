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