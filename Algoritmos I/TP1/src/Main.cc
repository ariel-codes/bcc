//
// Created by Ariel Santos on 30/06/21.
//

#include <iostream>
#include <Emparelhador.h>

#include "entrada.h"

int main(int argc, char *argv[]) {
    lista_postos postos = Entrada::ler_postos();
    lista_pessoas pessoas = Entrada::ler_pessoas();

    Emparelhador combinador(postos, pessoas);
    combinador.emparelhar_alocacoes();

    for (auto &&posto: postos) {
        std::cout << *posto << std::endl;
    }
    return 0;
}