//
// Created by Ariel Santos on 08/08/21.
//

#ifndef TP1_ALGORITMOTARJANMOD_H
#define TP1_ALGORITMOTARJANMOD_H

#include <stack>
#include <unordered_map>

#include "Vertice.h"
#include "ComponenteFConectado.h"


class AlgoritmoTarjanMod {
public:

    static int vertices_para_gfc(const std::unordered_map<int, VerticePtr> &);

private:

    void condensar_cfc(const VerticePtr& raiz);

    int indice = 0;
    std::stack<VerticePtr> pilha;
    int cfcs=0;
};



#endif //TP1_ALGORITMOTARJANMOD_H
