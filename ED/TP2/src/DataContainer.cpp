//
// Created by Ariel Santos on 02/03/21.
//

#include "DataContainer.hpp"

#include <utility>

DataContainer::DataContainer(std::string data, unsigned key) : data(std::move(data)), key(key) {}
bool DataContainer::operator<(const DataContainer &rhs) const {
  return key < rhs.key;
}
bool DataContainer::operator>(const DataContainer &rhs) const {
  return rhs < *this;
}
bool DataContainer::operator<=(const DataContainer &rhs) const {
  return !(rhs < *this);
}
bool DataContainer::operator>=(const DataContainer &rhs) const {
  return !(*this < rhs);
}
bool DataContainer::operator==(const DataContainer &rhs) const {
  return key == rhs.key;
}
bool DataContainer::operator!=(const DataContainer &rhs) const {
  return !(rhs == *this);
}
