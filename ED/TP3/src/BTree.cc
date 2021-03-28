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

Queue BTree::get_path(char node) {
  Queue path;

  if (node == root) {
	path.enqueue(0);
  } else if (node < root) {
	path.enqueue(-1);
	left->get_path(node, path);
  } else {
	path.enqueue(1);
	right->get_path(node, path);
  }

  return path;
}

void BTree::get_path(char node, Queue &path) {
  if (node == root) return;

  if (node < root) {
	path.enqueue(-1);
	left->get_path(node, path);
  } else {
	path.enqueue(1);
	right->get_path(node, path);
  }
}