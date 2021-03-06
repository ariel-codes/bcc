#include <fstream>
#include <cassert>

#include <Runner.hh>

int main(int argc, char *argv[]) {
  assert(argc == 2 && "Número de argumentos deve ser 1");

  std::ifstream file(argv[1]);
  char command;
  Runner runner;

  while (file.get(command)) {
	std::string text;
	file.ignore(2, ' ');
	std::getline(file, text);

	runner.run_command(CommandType(command), text);
  }

  return 0;
}