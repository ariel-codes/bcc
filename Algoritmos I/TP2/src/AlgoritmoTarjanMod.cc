//
// Created by Ariel Santos on 08/08/21.
//

#include <algorithm>
#include <iostream>

#include "AlgoritmoTarjanMod.h"
#include "ComponenteFConectado.h"

int AlgoritmoTarjanMod::vertices_para_gfc(const std::unordered_map<int, VerticePtr> &vertices) {
    AlgoritmoTarjanMod algoritmo;

    for (const auto &entrada : vertices) {
        const auto vertice = entrada.second;
        if (!vertice->foiIndexado())
            algoritmo.condensar_cfc(vertice);
    }
    return algoritmo.cfcs;
}

void AlgoritmoTarjanMod::condensar_cfc(const VerticePtr& raiz) {
    raiz->indice = indice;
    raiz->minimo_alcancavel = indice;
    indice++;
    pilha.push(raiz);
    raiz->esta_na_pilha = true;

    for (const auto &filho : raiz->arestas) {
        if (!filho->foiIndexado()) {
            condensar_cfc(filho);
            raiz->minimo_alcancavel = std::min(raiz->minimo_alcancavel, filho->minimo_alcancavel);
        } else if (filho->esta_na_pilha) {
            raiz->minimo_alcancavel = std::min(raiz->minimo_alcancavel, filho->indice);
        }
    }

    if (raiz->minimo_alcancavel == raiz->indice) {
        ComponenteFConectado novo_componente(raiz);
        VerticePtr filho;
        do {
            filho = pilha.top();
            filho->esta_na_pilha = false;
            pilha.pop();
        } while (filho && filho->indice != raiz->indice);
        cfcs++;
    }
}

