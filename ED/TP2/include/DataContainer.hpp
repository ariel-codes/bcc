//
// Created by Ariel Santos on 02/03/21.
//

#ifndef TP2_SRC_DATACONTAINER_HPP_
#define TP2_SRC_DATACONTAINER_HPP_

#include <string>
#include <ostream>

struct DataContainer {
  DataContainer() = default;
  DataContainer(std::string, unsigned);

  bool operator==(const DataContainer &rhs) const;
  bool operator!=(const DataContainer &rhs) const;
  bool operator<(const DataContainer &rhs) const;
  bool operator>(const DataContainer &rhs) const;
  bool operator<=(const DataContainer &rhs) const;
  bool operator>=(const DataContainer &rhs) const;
  friend std::ostream &operator<<(std::ostream &os, const DataContainer &container);

  std::string data;
  unsigned key{};
};

#endif //TP2_SRC_DATACONTAINER_HPP_
