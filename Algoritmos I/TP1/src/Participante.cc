//
// Created by Ariel Santos on 30/06/21.
//

#include "Participante.h"

unsigned int Participante::getIdentificador() const {
    return identificador;
}

local Participante::getLocalizacao() const {
    return localizacao;
}

double Participante::distancia(const Participante p) const {
    return localizacao.distancia(p.getLocalizacao());
}
