//
// Created by Ariel Santos on 05/03/21.
//

#include "sorting.hpp"
#include <iostream>

namespace {

void med3(Array &&array) {
  auto mid = array.size / 2;
  if (array[mid] < array[0]) {
	std::swap(array[mid], array[0]);
  }
  if (array.end() < array[0]) {
	std::swap(array.end(), array[0]);
  }
  if (array[mid] < array.end()) {
	std::swap(array[mid], array.end());
  }
}

void med3(Array &array) {
  med3(std::forward<Array>(array));
}

void prepare(Array &array) {
  if (array.size <= 7) return; // Não vale a pena
  if (array.size <= 40) {
	med3(array);
  } else { // Tukey's ninther
	auto third = array.size / 3;
	med3(array.view(0, third));
	med3(array.view(third - 1, third * 2));
	med3(array.view((third * 2) - 1));
  }
}

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

void quicksort_med3(Array &&array) {
  if (array.size < 2) return;

  prepare(array);
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

void sorting::quick_med3(Array &array) {
  quicksort_med3(std::forward<Array>(array));
}
