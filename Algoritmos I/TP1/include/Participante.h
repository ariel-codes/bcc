//
// Created by Ariel Santos on 28/06/21.
//

#ifndef TP3_PARTICIPANTE_H
#define TP3_PARTICIPANTE_H


#include "Localizacao.h"

class Participante {
public:
    Participante(unsigned id, local loc) : identificador(id), localizacao(loc) {};

    double distancia(const Participante) const;

    local getLocalizacao() const;

    unsigned int getIdentificador() const;

private:

    const unsigned identificador;
    const local localizacao;
};


#endif //TP3_PARTICIPANTE_H
