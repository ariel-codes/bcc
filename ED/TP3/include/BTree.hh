//
// Created by Ariel Santos on 24/03/21.
//

#ifndef TP3_SRC_BTREE_HH_
#define TP3_SRC_BTREE_HH_

#include <ostream>
class BTree {
 public:
  BTree() = default;
  explicit BTree(char root);

  void add_leaf(char leaf);

  friend std::ostream &operator<<(std::ostream &os, const BTree &tree);

 private:
  char root = 0;
  BTree *left = nullptr, *right = nullptr;
};

#endif //TP3_SRC_BTREE_HH_
