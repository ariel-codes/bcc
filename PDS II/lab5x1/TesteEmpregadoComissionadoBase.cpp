#include "EmpregadoComissionadoBase.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::string;

TEST_CASE("EmpregadoComissionadoBase: Salário base não pode ser < 0") {
  auto e = EmpregadoComissionadoBase("Ariel", "Santos", "117", 6, 5, 1999, 5000,
                                     0.2);
  e.setSalarioBase(-1000);
  CHECK(e.getSalarioBase() == 0);
}
TEST_CASE("EmpregadoComissionadoBase: Cálculo de salário") {
  auto e = EmpregadoComissionadoBase("Ariel", "Santos", "117", 6, 5, 1999, 5000,
                                     0.2);
  e.setSalarioBase(1000);
  CHECK(e.salario() == 2000.0);
}
TEST_CASE("EmpregadoComissionadoBase: Imprime salário") {
  std::stringstream out;
  auto e = EmpregadoComissionadoBase("Ariel", "Santos", "117", 6, 5, 1999, 5000,
                                     0.2, 1000);
  // redireciona stdout
  auto old_buf = std::cout.rdbuf(out.rdbuf());
  e.imprime();
  std::cout.rdbuf(old_buf); // reset

  CHECK(out.str() ==
        "Comissionado base empregado comissionado: Ariel Santos\n"
        "nascimento: Junho 5, 1999\n"
        "cpf: 117\n"
        "vendas brutas: 5000; taxa comissao: 0.2; salario base: 1000");
}