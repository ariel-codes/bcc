#include <stdexcept>
#include <fstream>

#include <Array.hpp>

int main(int argc, char *argv[]) {
  if (argc != 3)
	throw std::invalid_argument("Número de argumentos deve ser 2");

  std::ifstream file(argv[1]);
  Array array(std::stoul(argv[2]));

  for (size_t i = 0; i < array.size; ++i) {
	std::string name;
	unsigned distance;
	file >> name >> distance;
	array.items[i] = DataContainer(name, distance);
  }

  return 0;
}