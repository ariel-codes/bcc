#include "EmpregadoSalariado.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::string;
TEST_CASE("EmpregadoSalariado: Salário não pode ser negativo") {
  auto e = EmpregadoSalariado("Ariel", "Santos", "117", 6, 5, 1999, -1);
  CHECK(e.salario() == 0);
}
TEST_CASE("EmpregadoSalariado: imprime") {
  std::stringstream out;
  auto e = EmpregadoSalariado("Ariel", "Santos", "117", 6, 5, 1999, 500);

  // redireciona stdout
  auto old_buf = std::cout.rdbuf(out.rdbuf());
  e.imprime();
  std::cout.rdbuf(old_buf); // reset

  CHECK(out.str() == "empregado salariado: Ariel Santos\nnascimento: Junho "
                     "5, 1999\ncpf: 117\nsalario semanal: 500");
}