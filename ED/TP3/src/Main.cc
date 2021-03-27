#include <fstream>
#include <cassert>
#include <iostream>

#include <Runner.hh>

int main(int argc, char *argv[]) {
  assert(argc == 2 && "Número de argumentos deve ser 1");

  std::ifstream file(argv[1]);

  Runner runner;
  char command;
  while (file.get(command)) {
	std::string text;

	file.ignore(2, ' ');
	std::getline(file, text);
	runner.run_command(CommandType(command), text);
  }

  return 0;
}