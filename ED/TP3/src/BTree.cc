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

char BTree::get_node(Queue &coords) {
  if (!coords.empty()) {
	if (coords.dequeue() % 2 == 1) {
	  return left->get_node(coords);
	} else {
	  return right->get_node(coords);
	}
  }
  return root;
}
