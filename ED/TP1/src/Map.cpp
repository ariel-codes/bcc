//
// Created by Ariel Santos on 08/02/21.
//


#include <fstream>
#include "Map.hpp"

Map::Map(const std::string &filepath) {
  std::ifstream file(filepath);

  unsigned int height, width;
  file >> height;
  file >> width;
  points.reset(new QuadTree(height, width));

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      char point;
      file >> point;

      MapValue v;
      switch (point) {
        case 'R':v = Resource;
          break;
        case 'O':v = Obstacle;
          break;
        case 'H':v = Alien;
          break;
        default:continue;
      }

      assert(points->addPoint(x, y, v));
    }
  }
}
