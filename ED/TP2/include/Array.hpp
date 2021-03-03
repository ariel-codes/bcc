//
// Created by Ariel Santos on 02/03/21.
//

#ifndef TP2_SRC_ARRAY_HPP_
#define TP2_SRC_ARRAY_HPP_

#include <cstdlib>
#include <DataContainer.hpp>

struct Array {
  explicit Array(size_t size);

  const std::size_t size;
  DataContainer* items;
};

#endif //TP2_SRC_ARRAY_HPP_
