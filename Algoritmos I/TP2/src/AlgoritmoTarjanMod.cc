//
// Created by Ariel Santos on 01/08/21.
//

#include <algorithm>
#include <iostream>

#include "AlgoritmoTarjanMod.h"

int AlgoritmoTarjanMod::vertices_para_gfc(const std::unordered_map<int, VerticePtr> &vertices) {
    AlgoritmoTarjanMod algoritmo;

    for (const auto &entrada : vertices) {
        const auto vertice = entrada.second;
        if (!vertice->foiIndexado())
            algoritmo.condensar_cfc(vertice);
    }

    algoritmo.calcular_graus(vertices);

    int fontes = 0, vertedouros = 0, isolados = 0;
    for (const auto &cfc : algoritmo.componentes_fc) {
        if (cfc.second->grau_entrada == 0 && cfc.second->grau_saida > 0)
            fontes++;
        if (cfc.second->grau_entrada > 0 && cfc.second->grau_saida == 0)
            vertedouros++;
        if (cfc.second->grau_entrada == 0 && cfc.second->grau_saida == 0)
            isolados++;
    }
    return std::max(fontes + isolados, vertedouros + isolados);
}

void AlgoritmoTarjanMod::condensar_cfc(const VerticePtr &vertice) {
    vertice->indice = indice;
    vertice->minimo_alcancavel = indice;
    indice++;
    pilha.push(vertice);
    vertice->esta_na_pilha = true;

    for (const auto &filho : vertice->arestas) {
        if (!filho->foiIndexado()) {
            condensar_cfc(filho);
            vertice->minimo_alcancavel = std::min(vertice->minimo_alcancavel, filho->minimo_alcancavel);
        } else if (filho->esta_na_pilha) {
            vertice->minimo_alcancavel = std::min(vertice->minimo_alcancavel, filho->indice);
        }
    }

    if (vertice->minimo_alcancavel == vertice->indice) {
        VerticePtr filho;
        do {
            filho = pilha.top();
            filho->esta_na_pilha = false;
            filho->minimo_alcancavel = vertice->indice;
            pilha.pop();
        } while (filho && filho->indice != vertice->indice);
        componentes_fc.emplace(vertice->minimo_alcancavel, new ComponenteFConectado);
    }
}

void AlgoritmoTarjanMod::calcular_graus(const std::unordered_map<int, VerticePtr> &vertices) {
    for (const auto &entrada : vertices) {
        const auto fonte = entrada.second;
        for (const auto &destino : fonte->arestas) {
            if (fonte->minimo_alcancavel == destino->minimo_alcancavel) continue;

            auto cfc_fonte = componentes_fc.at(fonte->minimo_alcancavel);
            auto cfc_destino = componentes_fc.at(destino->minimo_alcancavel);

            cfc_fonte->grau_saida++;
            cfc_destino->grau_entrada++;
        }
    }
}