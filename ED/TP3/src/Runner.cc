//
// Created by Ariel Santos on 24/03/21.
//

#include <iostream>

#include "Queue.hh"
#include "Runner.hh"

void Runner::run_command(CommandType type, const std::string &text) {
  switch (type) {
	case CommandType::Load: load(text);
	  break;
	case CommandType::Decode: decode(text);
	  break;
	case CommandType::Encode: encode(text);
	  break;
  }
}

void Runner::load(const std::string &text) {
  parseTree = BTree(text.front());
  for (auto letter_it = text.begin() + 1; letter_it != text.end(); ++letter_it) {
	parseTree.add_leaf(*letter_it);
  }
}

void Runner::decode(const std::string &text) {
  Queue coords;

  for (auto c_it = text.begin() + 1; c_it != text.end(); ++c_it) {
	if ((*c_it) == 'x') {
	  std::cout << parseTree.get_node(coords);
	  coords = Queue();
	  continue;
	}
	coords.enqueue(*c_it);
  }

  std::cout << parseTree.get_node(coords) << std::endl;
}

void Runner::encode(const std::string &text) {

}
