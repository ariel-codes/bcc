//
// Created by Ariel Santos on 07/08/21.
//

#include "Vertice.h"

void Vertice::addAresta(const VerticePtr &destino) {
    arestas.push_back(destino);
}

bool Vertice::foiIndexado() const {
    return indice >= 0;
}