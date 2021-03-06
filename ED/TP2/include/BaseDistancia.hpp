//
// Created by Ariel Santos on 02/03/21.
//

#ifndef TP2_SRC_DATACONTAINER_HPP_
#define TP2_SRC_DATACONTAINER_HPP_

#include <string>
#include <ostream>

typedef unsigned int distance_t;

struct BaseDistancia {
  BaseDistancia() = default;
  BaseDistancia(std::string, distance_t);

  friend std::ostream &operator<<(std::ostream &, const BaseDistancia &);
  operator distance_t() const; // NOLINT(google-explicit-constructor)

  std::string data;
  distance_t distance{};
};

#endif //TP2_SRC_DATACONTAINER_HPP_
