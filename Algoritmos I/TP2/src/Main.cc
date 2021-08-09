//
// Created by Ariel Santos on 01/08/21.
//

#include <unordered_map>
#include <iostream>

#include "AlgoritmoTarjanMod.h"
#include "entrada.h"

int main(int argc, char *argv[]) {
    auto quantidades = Entrada::ler_quantidades();

    std::unordered_map<int, VerticePtr> aeroportos;
    for (int i = 1; i <= quantidades.first; ++i) {
        aeroportos.emplace(i, new Vertice);
    }

    Entrada::ler_rotas(quantidades.second, aeroportos);

    const int resposta = AlgoritmoTarjanMod::vertices_para_gfc(aeroportos);
    std::cout << resposta << std::endl;

    return 0;
}