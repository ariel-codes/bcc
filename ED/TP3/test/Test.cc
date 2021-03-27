//
// Created by Ariel Santos on 27/03/21.
//
#include <fstream>
#include <cassert>
#include <iostream>

#include <Runner.hh>

int main(int argc, char *argv[]) {
  assert(argc == 3 && "Número de argumentos deve ser 2");

  Runner runner;

  std::ifstream input(argv[1]);
  char command;
  while (input.get(command)) {
	if (CommandType(command) != CommandType::Load) {
	  input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	  continue;
	}

	std::string text;
	input.ignore(2, ' ');
	std::getline(input, text);
	runner.run_command(CommandType::Load, text);
  }
  input.close();

  std::ifstream output(argv[2]);
  std::string coded;
  while (std::getline(output, coded)) {
	if (coded.front() != 'x') continue;
	runner.run_command(CommandType::Decode, coded);
  }

  return 0;
}