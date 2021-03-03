//
// Created by Ariel Santos on 02/03/21.
//

#include "sorting.hpp"

void sorting::insertion(const Array &array) {
  for (size_t index = 1; index < array.size; ++index) {
	for (size_t i = index; i > 0 && array.items[i] < array.items[i - 1]; --i) {
	  std::swap(array.items[i], array.items[i - 1]);
	}
  }
}