#include "Piece.hpp"
#include "doctest.h"

TEST_CASE("Criação de peças diferentes"){
    Piece c("N", "8B","6C");
    CHECK(c.name == "Knight");
    Piece b("B", "8C","8C");
    CHECK(b.name == "Bishop");
    Piece r("R", "7A","7A");
    CHECK(r.name == "Rook");
}