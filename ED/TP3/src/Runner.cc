//
// Created by Ariel Santos on 24/03/21.
//

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

}

void Runner::encode(const std::string &text) {

}
