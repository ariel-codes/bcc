//
// Created by Ariel Santos on 01/08/21.
//

#include "Vertice.h"

void Vertice::addAresta(const VerticePtr &destino) {
    arestas.emplace_front(destino);
}

bool Vertice::foiIndexado() const {
    return indice >= 0;
}