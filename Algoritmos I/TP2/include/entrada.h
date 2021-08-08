//
// Created by Ariel Santos on 28/06/21.
//

#ifndef TP3_ENTRADA_H
#define TP3_ENTRADA_H

#include <memory>
#include <unordered_map>

#include "Aeroporto.h"

namespace Entrada {
    std::pair<int, int> ler_quantidades();

    void ler_rotas(int, std::unordered_map<int, AeroportoPtr>);
}

#endif //TP3_ENTRADA_H
