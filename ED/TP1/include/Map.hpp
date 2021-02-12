//
// Created by Ariel Santos on 08/02/21.
//

#ifndef TP1_SRC_MAP_HPP_
#define TP1_SRC_MAP_HPP_

#include <memory>
#include <string>
#include "QuadTree.hpp"

class Map {
 public:
  Map(const std::string&);
// private:
  std::unique_ptr<QuadTree> points;
};

#endif //TP1_SRC_MAP_HPP_
