//
// Created by Ariel Santos on 08/02/21.
//

#ifndef TP1_SRC_MAP_h_
#define TP1_SRC_MAP_h_

#include <memory>
#include <string>
#include "QuadTree.h"

class Map {
 public:
  explicit Map(const std::string &);

  PointValue getPoint(unsigned, unsigned);
  bool removePoint(unsigned, unsigned);

 private:
  std::unique_ptr<QuadTree> points;
};

#endif //TP1_SRC_MAP_h_
