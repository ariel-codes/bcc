//
// Created by Ariel Santos on 05/03/21.
//

#include "sorting.hpp"
#include <iostream>

namespace {

distance_t partition(Array &array) {
  // Aqui underflows não importam, serão corrigidos pelo ++index dps
  std::size_t index = -1;
  auto pivot_el = array.end();

  for (int i = 0; i < array.size - 1; ++i) {
	if (array[i] <= pivot_el)
	  std::swap(array[++index], array[i]);
  }
  std::swap(array[++index], array.end());

  return index;
}

void quicksort(Array &&array) {
  if (array.size < 2) return;

  auto index = partition(array);

  // Checar se 0 para prevenir underflow
  if (index)
	quicksort(array.view(0, index - 1));
  quicksort(array.view(index + 1));
}

}

void sorting::quick(Array &array) {
  quicksort(std::forward<Array>(array));
}