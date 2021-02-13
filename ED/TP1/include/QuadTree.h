//
// Created by Ariel Santos on 08/02/21.
//

#ifndef TP1_SRC_QUADTREE_h_
#define TP1_SRC_QUADTREE_h_

#include <array>

enum PointValue { OutOfBounds = 0, Empty, Resource, Alien, Obstacle, Mixed };

class QuadTree {
 public:
  QuadTree(unsigned, unsigned);
  QuadTree(unsigned, unsigned, unsigned);

  bool addPoint(unsigned, unsigned, PointValue);
  PointValue getPoint(unsigned, unsigned) const;

  PointValue get_area_value() const { return area_value; }

  bool operator==(const QuadTree &rhs) const {
    return area_value != Mixed && rhs.area_value != Mixed && area_value == rhs.area_value;
  }
  bool operator!=(const QuadTree &rhs) const {
    return !(rhs == *this);
  }

 private:
  PointValue area_value = Empty;
  unsigned start_x, start_y;
  uint32_t side_length;
  std::unique_ptr<QuadTree> children[4];

  bool isOutOfBounds(unsigned, unsigned) const;
  bool areChildrenEqual() const;
};

#endif //TP1_SRC_QUADTREE_h_
