//
// Created by Ariel Santos on 04/03/21.
//

#include "sorting.hpp"

namespace {

Array merge_arrays(const Array &left, const Array &right) {
  Array result(left.size + right.size);
  std::size_t l_index = 0, r_index = 0;

  while (l_index < left.size && r_index < right.size) {
	if (left[l_index] < right[r_index]) {
	  result[l_index + r_index] = left[l_index];
	  ++l_index;
	} else {
	  result[l_index + r_index] = right[r_index];
	  ++r_index;
	}
  }

  for (; l_index < left.size; ++l_index)
	result[l_index + r_index] = left[l_index];
  for (; r_index < right.size; ++r_index)
	result[l_index + r_index] = right[r_index];

  return result;
}

}

void sorting::merge(Array &array) {
  if (array.size < 2) return;

  auto middle = array.size / 2;
  auto left = array.view(0, middle), right = array.view(middle);

  merge(left);
  merge(right);

  array = merge_arrays(left, right);
}
