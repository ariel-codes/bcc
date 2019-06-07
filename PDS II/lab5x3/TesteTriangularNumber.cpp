#include "TriangularNumber.hpp"
#include "doctest.h"
#include <limits.h>

TEST_CASE("Números negativos: getElement") {
  CHECK_THROWS_AS(TriangularNumber::getElement(-1), InvalidTriangularNumber);
}
TEST_CASE("Números negativos: draw") {
  CHECK_THROWS_AS(TriangularNumber::draw(-1), InvalidTriangularNumber);
}
TEST_CASE("Overflow: getElement") {
  CHECK_THROWS_AS(TriangularNumber::getElement(INT_MAX),
                  InvalidTriangularNumber);
}
TEST_CASE("Overflow: draw") {
  CHECK_THROWS_AS(TriangularNumber::draw(INT_MAX), InvalidTriangularNumber);
}

TEST_CASE("draw: empty") { CHECK(TriangularNumber::draw(0) == string("")); }
TEST_CASE("draw: one") { CHECK(TriangularNumber::draw(1) == string("*")); }
TEST_CASE("draw: normal") {
  CHECK(TriangularNumber::draw(3) == string("*\n**\n***"));
}

TEST_CASE("getElement: empty") { CHECK(TriangularNumber::getElement(0) == 0); }
TEST_CASE("getElement: one") { CHECK(TriangularNumber::getElement(1) == 1); }
TEST_CASE("getElement: big") {
  CHECK(TriangularNumber::getElement(46340) == 1073720970);
}
