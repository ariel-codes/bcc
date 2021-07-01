//
// Created by Ariel Santos on 30/06/21.
//

#ifndef TP3_EMPARELHADOR_H
#define TP3_EMPARELHADOR_H

#include <utility>
#include <vector>

#include "Posto.h"
#include "Pessoa.h"

using namespace std;

class Emparelhador {
public:
    Emparelhador(lista_postos postos, lista_pessoas pessoas) : postos(std::move(postos)),
                                                               pessoas(std::move(pessoas)) {};

    void emparelhar_alocacoes();

private:
    void ordenar_pessoas();
    bool posto_disponivel();

    lista_postos postos;
    lista_pessoas pessoas;
};


#endif //TP3_EMPARELHADOR_H
