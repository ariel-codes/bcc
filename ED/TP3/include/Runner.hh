//
// Created by Ariel Santos on 24/03/21.
//

#ifndef TP3_SRC_RUNNER_HH_
#define TP3_SRC_RUNNER_HH_

#include <string>
#include "BTree.hh"

enum class CommandType : char {
  Load = 'A',
  Decode = 'D',
  Encode = 'C'
};

class Runner {
 public:
  Runner() = default;
  
  void run_command(CommandType type, const std::string &text);

 private:
  void load(const std::string &text);
  void decode(const std::string &text);
  void encode(const std::string &text);

  BTree parse_tree;
};

#endif //TP3_SRC_RUNNER_HH_
