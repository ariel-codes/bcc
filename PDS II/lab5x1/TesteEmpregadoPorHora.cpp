#include "EmpregadoPorHora.hpp"
#include "doctest.h"
#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::string;

TEST_CASE("EmpregadoSalariado: Cálculo de salário com horas extras") {
  auto e = EmpregadoPorHora("Ariel", "Santos", "117", 6, 5, 1999, 15, 50);
  CHECK(e.salario() == 825.0);
}
TEST_CASE("EmpregadoSalariado: imprime salario normal") {
  auto e = EmpregadoPorHora("Ariel", "Santos", "117", 6, 5, 1999, 15, 40);
  std::stringstream out;
  
  // redireciona stdout
  auto old_buf = std::cout.rdbuf(out.rdbuf());
  e.imprime();
  std::cout.rdbuf(old_buf); // reset

  CHECK(out.str() == "hourly employee: Ariel Santos\n"
                     "nascimento: Junho 5, 1999\n"
                     "cpf: 117\n"
                     "taxa por hora: 15; horas trabalhadas: 40");
}
