//
// Created by Ariel Santos on 12/02/21.
//

#ifndef TP1_SRC_COMMAND_H_
#define TP1_SRC_COMMAND_H_

#include <memory>

class Command {
 public:
  enum Type { Move, Collect, Eliminate, Activate, Execute, Report, Return };

  explicit Command(Type t, bool p = false) : type(t), dest_x(0), dest_y(0), priority(p) {}
  Command(Type t, unsigned x, unsigned y, bool p = false) : type(t), dest_x(x), dest_y(y), priority(p) {}

  Type get_type() const { return type; }
  unsigned get_dest_x() const { return dest_x; }
  unsigned get_dest_y() const { return dest_y; }
  bool get_priority() const { return priority; }

 private:
  const Type type;
  const unsigned dest_x, dest_y;
  const bool priority;
};

#endif //TP1_SRC_COMMAND_H_
