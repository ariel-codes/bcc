//
// Created by Ariel Santos on 30/06/21.
//

#include <ostream>

#include "Posto.h"
#include "Pessoa.h"

std::ostream &operator<<(std::ostream &os, const Posto &posto) {
    os << posto.getIdentificador() << std::endl;
    for (const auto &paciente : posto.alocados) {
        os << *paciente;
        if (paciente != posto.alocados.back()) os << " ";
    }
    return os;
}

bool Posto::cheio() const {
    return capacidade == alocados.size();
}

void Posto::alocar(const std::shared_ptr<Pessoa> &pessoa) {
    alocados.push_back(pessoa);
}
