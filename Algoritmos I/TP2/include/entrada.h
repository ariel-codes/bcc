//
// Created by Ariel Santos on 28/06/21.
//

#ifndef TP3_ENTRADA_H
#define TP3_ENTRADA_H

#include <utility>
#include <unordered_map>

#include "Vertice.h"

namespace Entrada {
    std::pair<int, int> ler_quantidades();

    void ler_rotas(int, std::unordered_map<int, VerticePtr>);
}

#endif //TP3_ENTRADA_H
