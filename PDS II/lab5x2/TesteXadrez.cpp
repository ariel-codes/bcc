#include "Piece.hpp"
#include "doctest.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

std::string capture_output(std::function<void()> fccall) {
  std::stringstream out;
  auto old_buf = std::cout.rdbuf(out.rdbuf()); // redireciona stdout
  fccall();
  std::cout.rdbuf(old_buf); // reset
  return out.str();
}

TEST_CASE("Piece: Criação de cavalo") {
  Piece c("N", "b8", "c6");
  CHECK(c.name == "Knight");
}
TEST_CASE("Piece: Criação de bispo") {
  Piece b("B", "c8", "c8");
  CHECK(b.name == "Bishop");
}
TEST_CASE("Piece: Criação de peão") {
  Piece r("R", "a7", "a7");
  r.setNextPosition("b5");
  CHECK(r.nextPosition == std::pair<int, int>(1, 5));
}
TEST_CASE("Piece: setNextPosition") {
  Piece c("N", "b8", "c6");
  CHECK(c.name == "Knight");
}
TEST_CASE("Knight: printPossibleMoves") {
  Knight c("N", "a3", "c4");
  c.setMovements();
  const std::string printPossibleMoves =
      capture_output([&c]() mutable -> void { c.printPossibleMoves(); });
  CHECK(printPossibleMoves == "(Knight) Current Position: (a3)\n"
                              "I have 4 legal movements.\n"
                              "(a3)->(b1)\n"
                              "(a3)->(b5)\n"
                              "(a3)->(c2)\n"
                              "(a3)->(c4)\n");
}
TEST_CASE("Bishop: printPossibleMoves") {
  Bishop b("B", "c1", "h6");
  b.setMovements();
  const std::string printPossibleMoves =
      capture_output([&b]() mutable -> void { b.printPossibleMoves(); });
  CHECK(printPossibleMoves == "(Bishop) Current Position: (c1)\n"
                              "I have 7 legal movements.\n"
                              "(c1)->(a3)\n"
                              "(c1)->(b2)\n"
                              "(c1)->(d2)\n"
                              "(c1)->(e3)\n"
                              "(c1)->(f4)\n"
                              "(c1)->(g5)\n"
                              "(c1)->(h6)\n");
}
TEST_CASE("Rook: printPossibleMoves") {
  Rook r("R", "b1", "b2");
  r.setMovements();
  const std::string printPossibleMoves =
      capture_output([&r]() mutable -> void { r.printPossibleMoves(); });
  CHECK(printPossibleMoves == "(Rook) Current Position: (b1)\n"
                              "I have 14 legal movements.\n"
                              "(b1)->(a1)\n"
                              "(b1)->(b2)\n"
                              "(b1)->(b3)\n"
                              "(b1)->(b4)\n"
                              "(b1)->(b5)\n"
                              "(b1)->(b6)\n"
                              "(b1)->(b7)\n"
                              "(b1)->(b8)\n"
                              "(b1)->(c1)\n"
                              "(b1)->(d1)\n"
                              "(b1)->(e1)\n"
                              "(b1)->(f1)\n"
                              "(b1)->(g1)\n"
                              "(b1)->(h1)\n");
}
TEST_CASE("Knight: checkMovement") {
  Knight c("N", "a3", "c4");
  c.setMovements();
  const std::string checkMovement =
      capture_output([&c]() mutable -> void { c.checkMovement(); });
  CHECK_EQ(checkMovement, "Moving from (a3) to (c4)\n"
                          "I cannot move from (c4) to (c4)\n");
}
TEST_CASE("Bishop: checkMovement") {
  Bishop b("B", "e3", "b6");
  b.setMovements();
  const std::string checkMovement =
      capture_output([&b]() mutable -> void { b.checkMovement(); });
  CHECK_EQ(checkMovement, "Moving from (e3) to (b6)\n"
                          "I cannot move from (b6) to (b6)\n");
}
TEST_CASE("Rook: checkMovement") {
  Rook r("R", "d2", "d5");
  r.setMovements();
  const std::string checkMovement =
      capture_output([&r]() mutable -> void { r.checkMovement(); });
  CHECK_EQ(checkMovement, "Moving from (d2) to (d5)\n"
                          "I cannot move from (d5) to (d5)\n");
}