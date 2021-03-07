//
// Created by Ariel Santos on 07/03/21.
//

#include <iostream>

#include "sorting.hpp"

namespace {
void run_cycle(Array &array, std::size_t start) {
  // Primeiro, encontramos a posição correta de `item`
  std::size_t correct_pos = 0;
  for (int i = 0; i < array.size; ++i) {
	if (i == start) continue;
	if (array[i] < array[start]) correct_pos++;
  }

  // É preciso descontar os casos de números repetidos
  while (array[correct_pos] == array[start]) {
	if (correct_pos == start) return;
	correct_pos++;
  }

  std::swap(array[correct_pos], array[start]);
  run_cycle(array, start);
}

}

void sorting::cycle(Array &array) {
  for (std::size_t cycle_start = 0; cycle_start < array.size; ++cycle_start) {
	run_cycle(array, cycle_start);
  }
}