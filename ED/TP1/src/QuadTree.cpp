//
// Created by Ariel Santos on 08/02/21.
//
#include <stdexcept>
#include "QuadTree.hpp"

QuadTree::QuadTree(unsigned int size_x, unsigned int size_y) {
//  https://jameshfisher.com/2018/03/30/round-up-power-2/ & https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
  side_length = __builtin_clz(size_x > size_y ? size_x : size_y);
  start_x = 0;
  start_y = 0;
}
QuadTree::QuadTree(unsigned int x, unsigned int y, unsigned int size) : start_x(x), start_y(y), side_length(size) {}

bool QuadTree::isOutOfBounds(unsigned int x, unsigned int y) const {
  return !(x > (start_x + side_length) || y > (start_y + side_length) || x < start_x || y < start_y);
}

bool QuadTree::addPoint(unsigned int x, unsigned int y, MapValue p_value) {
  if (isOutOfBounds(x, y)) return false;

  if (p_value == area_value) return true;
  if (side_length == 1) {
    area_value = p_value;
    return true;
  }

  children[0] = new QuadTree(start_x, start_y, side_length / 2);
  children[1] = new QuadTree(start_x + (side_length / 2), start_y, side_length / 2);
  children[2] = new QuadTree(start_x, start_y + (side_length / 2), side_length / 2);
  children[3] = new QuadTree(start_x + (side_length / 2), start_y + side_length / 2, side_length / 2);

  for (auto &i : children) {
    if (i->addPoint(x, y, p_value)) {
      area_value = Mixed;
      return true;
    }
  }

  throw std::out_of_range("Erro Fatal");
}

MapValue QuadTree::getPoint(unsigned int x, unsigned int y) const {
  if (isOutOfBounds(x, y)) return OutOfBounds;

  if (area_value != Mixed) return area_value;

  for (auto &i : children) {
    if (i->getPoint(x, y) != OutOfBounds)
      return i->get_area_value();
  }

  throw std::out_of_range("Erro Fatal");
}
