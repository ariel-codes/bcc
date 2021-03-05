//
// Created by Ariel Santos on 02/03/21.
//

#ifndef TP2_SRC_ARRAY_HPP_
#define TP2_SRC_ARRAY_HPP_

#include <cstdlib>
#include <DataContainer.hpp>
#include <ostream>

struct Array {
  explicit Array(std::size_t size);
  Array(Array const &, std::size_t start);
  Array(Array const &, std::size_t start, std::size_t end);

  DataContainer &operator[](std::size_t) const;
  friend std::ostream &operator<<(std::ostream &os, const Array &array);

  std::size_t size;
  DataContainer *items;
};

#endif //TP2_SRC_ARRAY_HPP_
