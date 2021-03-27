//
// Created by Ariel Santos on 24/03/21.
//

#ifndef TP3_SRC_BTREE_HH_
#define TP3_SRC_BTREE_HH_

#include <ostream>

#include "Queue.hh"

class BTree {
 public:
  BTree() = default;
  explicit BTree(char root);

  void add_leaf(char leaf);
  char get_node(Queue &coords);
  Queue get_path(char node);

 private:
  void get_path(char node, Queue &path);
  
  char root = 0;
  BTree *left = nullptr, *right = nullptr;
};

#endif //TP3_SRC_BTREE_HH_
