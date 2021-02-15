//
// Created by Ariel Santos on 08/02/21.
//

#include <cassert>
#include <fstream>

#include "Map.h"

Map::Map(const std::string &filepath) {
  std::ifstream file(filepath);

  unsigned height, width;
  file >> height;
  file >> width;
  points.reset(new QuadTree(height, width));

  for (unsigned y = 0; y < height; ++y) {
    for (unsigned x = 0; x < width; ++x) {
      char point;
      file >> point;

      PointValue v;
      switch (point) {
        case 'R': v = Resource;
          break;
        case 'O': v = Obstacle;
          break;
        case 'H': v = Alien;
          break;
        default: v = Empty;
      }

      assert(points->addPoint(x, y, v));
    }
  }
}

PointValue Map::getPoint(unsigned x, unsigned y) {
  return points->getPoint(x, y);
}

bool Map::removePoint(unsigned x, unsigned y) {
  return points->addPoint(x, y, Empty);
}
