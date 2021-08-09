//
// Created by Ariel Santos on 01/08/21.
//

#ifndef TP1_VERTICE_H
#define TP1_VERTICE_H

#include <memory>
#include <forward_list>

struct Vertice {
    friend class AlgoritmoTarjanMod;

    void addAresta(const std::shared_ptr<Vertice> &destino);

    bool foiIndexado() const;

    std::forward_list<std::shared_ptr<Vertice>> arestas;
    int indice = -1; // -1 == não indexado
    int minimo_alcancavel = -1;
    bool esta_na_pilha = false;
};

typedef std::shared_ptr<Vertice> VerticePtr;


#endif //TP1_VERTICE_H
