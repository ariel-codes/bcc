//
// Created by Ariel Santos on 02/03/21.
//

#include "BaseDistancia.hpp"

#include <utility>

BaseDistancia::BaseDistancia(std::string data, distance_t key) : data(std::move(data)), distance(key) {}

BaseDistancia::operator distance_t() const {
  return distance;
}

std::ostream &operator<<(std::ostream &os, const BaseDistancia &container) {
  os << container.data << " " << container.distance << std::endl;
  return os;
}
