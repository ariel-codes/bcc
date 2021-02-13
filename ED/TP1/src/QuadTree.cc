//
// Created by Ariel Santos on 08/02/21.
//
#include <stdexcept>
#include <cassert>
#include "QuadTree.h"

QuadTree::QuadTree(unsigned size_x, unsigned size_y) {
//  https://jameshfisher.com/2018/03/30/round-up-power-2/ & https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
  uint32_t larger_side = size_x > size_y ? size_x : size_y;
  side_length = 1 << (32 - __builtin_clz(larger_side - 1));
  start_x = 0;
  start_y = 0;
}
QuadTree::QuadTree(unsigned x, unsigned y, unsigned size) : start_x(x), start_y(y), side_length(size) {}

bool QuadTree::addPoint(unsigned x, unsigned y, PointValue p_value) {
  if (isOutOfBounds(x, y)) return false;

  if (p_value == area_value) return true;
  if (side_length == 1) {
    area_value = p_value;
    return true;
  }

  if (area_value != Mixed) {
    children[0].reset(new QuadTree(start_x, start_y, side_length / 2));
    children[1].reset(new QuadTree(start_x + (side_length / 2), start_y, side_length / 2));
    children[2].reset(new QuadTree(start_x, start_y + (side_length / 2), side_length / 2));
    children[3].reset(new QuadTree(start_x + (side_length / 2), start_y + side_length / 2, side_length / 2));
  }

  for (auto &i : children) {
    if (i->addPoint(x, y, p_value)) {
      if (areChildrenEqual()) {
        for (auto &c : children) c.reset();
        area_value = p_value;
      } else {
        area_value = Mixed;
      }
      return true;
    }
  }

  assert(false);
}

PointValue QuadTree::getPoint(unsigned x, unsigned y) const {
  if (isOutOfBounds(x, y)) return OutOfBounds;

  if (area_value != Mixed) return area_value;

  for (auto &i : children) {
    if (i->getPoint(x, y) != OutOfBounds)
      return i->get_area_value();
  }

  assert(false);
}

bool QuadTree::isOutOfBounds(unsigned x, unsigned y) const {
  return x > (start_x + side_length) || y > (start_y + side_length) || x < start_x || y < start_y;
}

bool QuadTree::areChildrenEqual() const {
  bool equal = true;
  for (int i = 0; i < 3; ++i) {
    equal &= (*children[i]) == (*children[i + 1]);
  }

  return equal;
}
