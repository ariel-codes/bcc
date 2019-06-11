#include "doctest.h"
#include "Estudante.hpp"

TEST_CASE("Presença > 100%")
{
    CHECK_THROWS_AS(Estudante::determinarAprovacao(0, 0, 1.2), ErroDeterminarAprovacao);
}
TEST_CASE("Presença < 0%")
{
    CHECK_THROWS_AS(Estudante::determinarAprovacao(0, 0, -0.1), ErroDeterminarAprovacao);
}

TEST_CASE("Nota final > 100%")
{
    CHECK_THROWS_AS(Estudante::determinarAprovacao(105, 0, 0), ErroDeterminarAprovacao);
}
TEST_CASE("Nota final < 0%")
{
    CHECK_THROWS_AS(Estudante::determinarAprovacao(-1, 0, 0), ErroDeterminarAprovacao);
}

TEST_CASE("Nota especial > 100%")
{
    CHECK_THROWS_AS(Estudante::determinarAprovacao(0, 150, 0), ErroDeterminarAprovacao);
}
TEST_CASE("Nota especial < 0%")
{
    CHECK_THROWS_AS(Estudante::determinarAprovacao(0, -50, 0), ErroDeterminarAprovacao);
}

TEST_CASE("Conceito F por nota")
{
    CHECK_EQ(Estudante::determinarAprovacao(35, 0, 0.75), false);
}
TEST_CASE("Conceito F por presença")
{
    CHECK_EQ(Estudante::determinarAprovacao(65, 0, 0.50), false);
}
TEST_CASE("Conceito F por especial")
{
    CHECK_EQ(Estudante::determinarAprovacao(40, 70, 0.75), false);
}

TEST_CASE("Conceito E")
{
    CHECK_EQ(Estudante::determinarAprovacao(55, 75, 0.75), true);
}

TEST_CASE("Conceito D")
{
    CHECK_EQ(Estudante::determinarAprovacao(60, 0, 0.75), true);
}

TEST_CASE("Conceito A")
{
    CHECK_EQ(Estudante::determinarAprovacao(100, 0, 1), true);
}