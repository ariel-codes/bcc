//
// Created by Ariel Santos on 12/02/21.
//

#ifndef TP1_SRC_COMMAND_H_
#define TP1_SRC_COMMAND_H_

#include <memory>

enum CmdType { Move, Collect, Eliminate, Activate, Execute, Report, Return };

class Command {
 public:
  explicit Command(CmdType t, bool p = false) : type(t), dest_x(0), dest_y(0), priority(p) {}
  Command(CmdType t, unsigned x, unsigned y, bool p = false) : type(t), dest_x(x), dest_y(y), priority(p) {}

  const CmdType type;
  const unsigned dest_x, dest_y;
  const bool priority;
};

#endif //TP1_SRC_COMMAND_H_
