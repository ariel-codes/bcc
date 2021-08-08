//
// Created by Ariel Santos on 28/06/21.
//

#include <iostream>

#include "entrada.h"

int main(int argc, char *argv[]) {
    auto quantidades = Entrada::ler_quantidades();

    std::unordered_map<int, AeroportoPtr> aeroportos;
    for (int i = 1; i <= quantidades.first; ++i) {
        aeroportos.emplace(i, new Aeroporto);
    }

    Entrada::ler_rotas(quantidades.second, aeroportos);

    return 0;
}