//
// Created by Ariel Santos on 08/02/21.
//

#ifndef TP1_SRC_QUADTREE_HPP_
#define TP1_SRC_QUADTREE_HPP_

#include "values.hpp"

class QuadTree {
 public:
  QuadTree(unsigned int, unsigned int);
  QuadTree(unsigned int x, unsigned int y, unsigned int size);

  bool addPoint(unsigned int, unsigned int, MapValue);
  MapValue getPoint(unsigned int, unsigned int) const;

  MapValue get_area_value() const { return area_value; }

 private:
  MapValue area_value = Empty;
  unsigned int start_x, start_y, side_length;
  QuadTree *children[4] = {nullptr, nullptr, nullptr, nullptr};

  bool isOutOfBounds(unsigned int, unsigned int) const;
};

#endif //TP1_SRC_QUADTREE_HPP_
