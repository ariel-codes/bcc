//
// Created by Ariel Santos on 02/03/21.
//

#ifndef TP2_SRC_ARRAY_HPP_
#define TP2_SRC_ARRAY_HPP_

#include <cstdlib>
#include <ostream>

#include "BaseDistancia.hpp"

struct Array {
  explicit Array(std::size_t size);

  /// Cria uma view de \a array a partir de \a start até o fim do \a array
  Array view(std::size_t start);
  /// Cria uma view de \a array a partir de \a start até \a end
  Array view(std::size_t start, std::size_t end);
  /// Retorna último \em BaseDistancia do Array
  BaseDistancia &end() const;

  BaseDistancia &operator[](std::size_t) const;
  friend std::ostream &operator<<(std::ostream &os, const Array &array);

  std::size_t size;
  BaseDistancia *items;

 private:
  Array(Array &array, std::size_t start, std::size_t end);
};

#endif //TP2_SRC_ARRAY_HPP_
