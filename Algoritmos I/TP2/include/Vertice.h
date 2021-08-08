//
// Created by Ariel Santos on 07/08/21.
//

#ifndef TP1_VERTICE_H
#define TP1_VERTICE_H

#include <memory>
#include <vector>

struct Vertice;

typedef std::shared_ptr<Vertice> VerticePtr;

struct Vertice {
    friend class AlgoritmoTarjanMod;

    void addAresta(const VerticePtr &destino);

    bool foiIndexado() const;

    std::vector<VerticePtr> arestas;
    int indice = -1; // -1 == não indexado
    bool esta_na_pilha = false;
    int minimo_alcancavel = -1;
};


#endif //TP1_VERTICE_H
