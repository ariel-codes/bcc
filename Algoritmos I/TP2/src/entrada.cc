//
// Created by Ariel Santos on 28/06/21.
//
#include <iostream>
#include <utility>

#include <entrada.h>

namespace Entrada {

    std::pair<int, int> ler_quantidades() {
        int n_aeroportos, n_rotas;
        std::cin >> n_aeroportos >> n_rotas;
        return std::make_pair(n_aeroportos, n_rotas);
    }

    void ler_rotas(int n_rotas, std::unordered_map<int, AeroportoPtr> aeroportos) {
        for (int i = 0; i < n_rotas; ++i) {
            int origem, destino;
            std::cin >> origem >> destino;
            auto aeroporto = aeroportos.at(origem);
            aeroporto->add_destino(aeroportos.at(destino));
        }
    }
}