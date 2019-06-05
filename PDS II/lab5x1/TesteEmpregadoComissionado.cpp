#include "EmpregadoComissionado.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::string;

TEST_CASE("EmpregadoComissionado: Comissão não pode ser > 100%") {
  auto e = EmpregadoComissionado("Ariel", "Santos", "117", 6, 5, 1999, 5000);
  e.setTaxaComissao(4);
  CHECK(e.getTaxaComissao() == 0);
}
TEST_CASE("EmpregadoComissionado: Cálculo de salário") {
  auto e =
      EmpregadoComissionado("Ariel", "Santos", "117", 6, 5, 1999, 5000, 0.2);
  CHECK(e.salario() == 1000.0);
}

TEST_CASE("EmpregadoComissionado: Imprime") {
  auto e =
      EmpregadoComissionado("Ariel", "Santos", "117", 6, 5, 1999, 5000, 0.2);
  std::stringstream out;

  // redireciona stdout
  auto old_buf = std::cout.rdbuf(out.rdbuf());
  e.imprime();
  std::cout.rdbuf(old_buf); // reset

  CHECK(out.str() == "empregado comissionado: Ariel Santos\n"
                     "nascimento: Junho 5, 1999\n"
                     "cpf: 117\n"
                     "vendas brutas: 5000; taxa comissao: 0.2");
}