//
// Created by Ariel Santos on 08/08/21.
//

#ifndef TP1_COMPONENTEFCONECTADO_H
#define TP1_COMPONENTEFCONECTADO_H


#include "Vertice.h"

struct ComponenteFConectado {
    friend class AlgoritmoTarjanMod;

    explicit ComponenteFConectado(VerticePtr raiz);

    const VerticePtr raiz;
};


#endif //TP1_COMPONENTEFCONECTADO_H
