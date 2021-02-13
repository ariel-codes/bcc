//
// Created by Ariel Santos on 08/02/21.
//

#ifndef TP1_SRC_ROBOT_h_
#define TP1_SRC_ROBOT_h_

#include <memory>
#include <string>
#include <utility>
#include <iostream>
#include <sstream>

#include "Queue.h"
#include "Command.h"
#include "Map.h"

class Robot {
 public:
  explicit Robot(unsigned id, std::shared_ptr<Map> map) : id(id), map(std::move(map)) {};

  void addCommand(Command);
  void resetState();

  unsigned get_resource_count() const;
  unsigned get_alien_count() const;

 private:
  void move(unsigned x, unsigned y);
  void collect();
  void eliminate();
  void activate();
  void execute();
  void report();
  void endMission() const;
  void robotPrint(const std::string &) const;
  static void basePrint(const std::string &);

  unsigned id;
  std::shared_ptr<Map> map;
  std::unique_ptr<Queue<Command>> commands = std::unique_ptr<Queue<Command>>(new Queue<Command>);
  std::unique_ptr<Queue<std::string>> history = std::unique_ptr<Queue<std::string>>(new Queue<std::string>);
  unsigned resource_count = 0, alien_count = 0;
  unsigned pos_x = 0, pos_y = 0;
  bool active = false;
};

#endif //TP1_SRC_ROBOT_h_
