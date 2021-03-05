//
// Created by Ariel Santos on 02/03/21.
//

#include "Array.hpp"

Array::Array(std::size_t size) : size(size), items(new DataContainer[size]) {}

Array::Array(const Array &array, std::size_t start) : size(array.size - start), items(&array[start]) {}

Array::Array(const Array &array, std::size_t start, std::size_t end) : size(end - start), items(&array[start]) {}

DataContainer &Array::operator[](std::size_t i) const {
  return items[i];
}

std::ostream &operator<<(std::ostream &os, const Array &array) {
  for (size_t i = array.size; i-- > 0;) {
	os << array[i];
  }
  return os;
}

