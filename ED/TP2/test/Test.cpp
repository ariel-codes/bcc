//
// Created by Ariel Santos on 07/03/21.
//
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <cassert>

#include "Array.hpp"
#include "sorting.hpp"

void test_sort(Array &array, void (*sort)(Array &)) {
  auto sorted = new Array(array.size);
  std::copy(array.items, &array.end(), sorted->items);
  sort(*sorted);
  for (size_t i = 0; i < array.size - 1; ++i) {
	assert((*sorted)[i] <= (*sorted)[i + 1]);
  }
  delete sorted;
}

int main(int argc, char *argv[]) {
  assert(argc == 3 && "Número de argumentos deve ser 2");

  std::ifstream file(argv[1]);
  Array array(std::stoul(argv[2]));

  for (size_t i = 0; i < array.size; ++i) {
	std::string name;
	distance_t distance;
	assert((file >> name >> distance) && "Arquivo mal-formado");
	array[i] = BaseDistancia(name, distance);
  }

  test_sort(array, sorting::insertion);
  test_sort(array, sorting::merge);
  test_sort(array, sorting::quick);
  test_sort(array, sorting::quick_med3);
  test_sort(array, sorting::cycle);

  return 0;
}