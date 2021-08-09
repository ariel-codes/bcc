//
// Created by Ariel Santos on 01/08/21.
//

#ifndef TP1_COMPONENTEFCONECTADO_H
#define TP1_COMPONENTEFCONECTADO_H

#include <memory>

struct ComponenteFConectado {
    friend class AlgoritmoTarjanMod;

    int grau_entrada = 0, grau_saida = 0;
};

typedef std::shared_ptr<ComponenteFConectado> ComponenteFCPtr;


#endif //TP1_COMPONENTEFCONECTADO_H
