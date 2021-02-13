//
// Created by Ariel Santos on 08/02/21.
//

#ifndef TP1_SRC_BASE_h_
#define TP1_SRC_BASE_h_

#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>

#include "Queue.h"
#include "Robot.h"
#include "Map.h"

class Base {
 public:
  explicit Base(const std::string &);
  void parseCommands(const std::string &);
  void printResult() const;

 private:
  std::shared_ptr<Map> map;
  std::vector<std::unique_ptr<Robot>> robots = std::vector<std::unique_ptr<Robot>>(50);
  unsigned resource_count = 0;
  unsigned alien_count = 0;
};

#endif //TP1_SRC_BASE_h_
