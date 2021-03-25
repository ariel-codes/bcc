//
// Created by Ariel Santos on 24/03/21.
//

#include <cassert>

#include "BTree.hh"

BTree::BTree(char root) : root(root) {}

void BTree::add_leaf(char leaf) {
  assert(leaf != root);
  if (leaf < root) {
	if (left != nullptr) left->add_leaf(leaf);
	else left = new BTree(leaf);
  } else {
	if (right != nullptr) right->add_leaf(leaf);
	else right = new BTree(leaf);
  }
}

std::ostream &operator<<(std::ostream &os, const BTree &tree) {
  if (tree.left) os << (*tree.left);
  if (tree.right) os << (*tree.right);
  return os;
}
