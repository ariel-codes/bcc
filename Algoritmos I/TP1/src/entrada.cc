//
// Created by Ariel Santos on 28/06/21.
//

#include <iostream>
#include <vector>
#include <memory>

#include <Posto.h>
#include <Pessoa.h>


namespace Entrada {
    lista_postos ler_postos() {
        int quantidade;
        std::cin >> quantidade;
        lista_postos postos(quantidade);

        for (int i = 0; i < quantidade; ++i) {
            unsigned capacidade, loc_x, loc_y;
            std::cin >> capacidade, std::cin >> loc_x, std::cin >> loc_y;
            postos[i] = std::make_shared<Posto>(i, Localizacao(loc_x, loc_y), capacidade);
        }
        return postos;
    }

    lista_pessoas ler_pessoas() {
        int quantidade;
        std::cin >> quantidade;
        lista_pessoas pessoas(quantidade);

        for (int i = 0; i < quantidade; ++i) {
            unsigned idade, loc_x, loc_y;
            std::cin >> idade, std::cin >> loc_x, std::cin >> loc_y;
            pessoas[i] = std::make_shared<Pessoa>(i, Localizacao(loc_x, loc_y), idade);
        }
        return pessoas;
    }
}