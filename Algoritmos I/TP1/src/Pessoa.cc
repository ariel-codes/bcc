//
// Created by Ariel Santos on 28/06/21.
//

#include <memory>
#include <utility>
#include <algorithm>
#include <cmath>

#include "Pessoa.h"

std::ostream &operator<<(std::ostream &os, const Pessoa &pessoa) {
    os << pessoa.getIdentificador();
    return os;
}

unsigned int Pessoa::getIdade() const {
    return idade;
}

void Pessoa::inicializar_preferencias(const lista_postos &postos) {
    preferencias = std::make_unique<Preferencias>(*this, postos);
}

std::shared_ptr<Posto> Pessoa::proxima_preferencia() {
    return preferencias->proxima();
}

// Copiado do Knuth
bool Pessoa::Preferencias::quase_igual(double a, double b) {
    auto epsilon = std::max(a, b) * 0.01; // 1% de erro relativo?? valor semi-arbitrário
    return std::abs(a - b) <= ((std::abs(a) < std::abs(b) ? std::abs(b) : std::abs(a)) * epsilon);
}

Pessoa::Preferencias::Preferencias(const Pessoa &pessoa, lista_postos postos) {
    // queremos preservar o desempate por ID
    std::stable_sort(postos.begin(), postos.end(),
                     [&pessoa](const std::shared_ptr<Posto> &a, const std::shared_ptr<Posto> &b) {
                         auto distancia_a = pessoa.distancia(*a), distancia_b = pessoa.distancia(*b);
                         if (!quase_igual(distancia_a, distancia_b))
                             return distancia_a < distancia_b;
                         else return a->getIdentificador() < b->getIdentificador();
                     });

    for (const auto &posto: postos) preferencias.push(posto);
}

std::shared_ptr<Posto> Pessoa::Preferencias::proxima() {
    if (preferencias.empty()) return nullptr;

    auto prox = preferencias.front();
    preferencias.pop();
    return prox;
}
