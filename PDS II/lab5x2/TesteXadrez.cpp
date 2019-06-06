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

TEST_CASE("Criação de cavalo") {
  Piece c("N", "b8", "c6");
  CHECK(c.name == "Knight");
}
TEST_CASE("Criação de bispo") {
  Piece b("B", "c8", "c8");
  CHECK(b.name == "Bishop");
}
TEST_CASE("Criação de peão") {
  Piece r("R", "a7", "a7");
  CHECK(r.name == "Rook");
}
TEST_CASE("asd") {
  Piece c("N", "a3", "c4");
  const std::string printPossibleMoves =
      capture_output([&c]() mutable -> void { c.printPossibleMoves(); });
  CHECK(printPossibleMoves == "I can move from (a3) to (c4)");
}
