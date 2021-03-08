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

std::ptrdiff_t partition(Array &array, distance_t pivot) {
  ptrdiff_t i = 0;
  for (ptrdiff_t j = array.size - 1;; i++, j--) {
	while (array[i] < pivot) i++;
	while (array[j] > pivot) j--;
	if (i >= j) break;
	std::swap(array[i], array[j]);
  }
  return i;
}

void quicksort(Array &&array) {
  if (array.size < 2) return;

  distance_t pivot = array.items[array.size / 2];
  std::ptrdiff_t i = partition(array, pivot);

  quicksort(array.view(0, i));
  quicksort(array.view(i));
}

void quicksort_med3(Array &&array) {
  if (array.size < 2) return;

  prepare(array);
  distance_t pivot = array.end();
  std::ptrdiff_t i = partition(array, pivot);

  quicksort_med3(array.view(0, i));
  quicksort_med3(array.view(i));
}

}

void sorting::quick(Array &array) {
  quicksort(std::forward<Array>(array));
}

void sorting::quick_med3(Array &array) {
  quicksort_med3(std::forward<Array>(array));
}
