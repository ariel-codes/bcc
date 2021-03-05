#include <stdexcept>
#include <fstream>
#include <iostream>
#include <cassert>

#include "Array.hpp"
#include "sorting.hpp"

int main(int argc, char *argv[]) {
  assert(argc == 3 && "Número de argumentos deve ser 2");

  std::ifstream file(argv[1]);
  Array array(std::stoul(argv[2]));

  for (size_t i = 0; i < array.size; ++i) {
	std::string name;
	unsigned distance;
	assert((file >> name >> distance) && "Arquivo mal-formado");
	array[i] = DataContainer(name, distance);
  }

  sorting::merge(array);

  std::cout << array;

  return 0;
}