//
// Created by Ariel Santos on 30/06/21.
//

#include <cmath>

#include "Localizacao.h"

double Localizacao::distancia(Localizacao outra) const {
    const auto quadradoX = pow((int(x) - int(outra.x)), 2);
    const auto quadradoY = pow((int(y) - int(outra.y)), 2);
    return sqrt(quadradoX + quadradoY);
}

std::ostream &operator<<(std::ostream &os, const Localizacao &localizacao) {
    os << "(x: " << localizacao.x << " y: " << localizacao.y << ")";
    return os;
}
