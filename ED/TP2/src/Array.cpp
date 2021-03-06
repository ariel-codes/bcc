//
// Created by Ariel Santos on 02/03/21.
//
#include <utility>

#include "Array.hpp"

Array::Array(std::size_t size) : size(size), items(new BaseDistancia[size]) {}

Array Array::view(std::size_t start) {
  return Array{*this, start, size};
}

Array Array::view(std::size_t start, std::size_t end) {
  return Array{*this, start, end};
}

Array::Array(Array &array, std::size_t start, std::size_t end) : size(end - start), items(&array[start]) {
  if (start > end) throw;
}

BaseDistancia &Array::end() const {
  return items[size - 1];
}

BaseDistancia &Array::operator[](std::size_t i) const {
  return items[i];
}

std::ostream &operator<<(std::ostream &os, const Array &array) {
  for (size_t i = array.size; i-- > 0;) {
	os << array[i];
  }
  return os;
}

