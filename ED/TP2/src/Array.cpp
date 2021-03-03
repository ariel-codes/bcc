//
// Created by Ariel Santos on 02/03/21.
//

#include "Array.hpp"

Array::Array(size_t size) : size(size), items(new DataContainer[size]) {}
