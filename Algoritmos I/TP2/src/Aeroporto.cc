//
// Created by Ariel Santos on 07/08/21.
//

#include "Aeroporto.h"

void Aeroporto::add_destino(const AeroportoPtr& destino) {
    destinos.push_back(destino);
}
