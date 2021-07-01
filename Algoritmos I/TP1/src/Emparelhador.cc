//
// Created by Ariel Santos on 30/06/21.
//

#include <algorithm>

#include "Emparelhador.h"

void Emparelhador::emparelhar_alocacoes() {
    // queremos preservar o desempate por ID
    ordenar_pessoas();
    lista_pessoas::size_type indice_pessoas = 0;

    // as preferências de todos os postos são iguais então podemos tratar como uma lista de espera
    while (posto_disponivel() && indice_pessoas < pessoas.size()) {
        auto pessoa = pessoas[indice_pessoas++];
        // cálculo de distancias é custoso, e nem sempre vamos tocar em todas pessoas
        pessoa->inicializar_preferencias(postos);

        auto posto_ideal = pessoa->proxima_preferencia();
        while (posto_ideal->cheio()) posto_ideal = pessoa->proxima_preferencia();

        posto_ideal->alocar(pessoa);
    }
}

void Emparelhador::ordenar_pessoas() {
    std::stable_sort(pessoas.begin(), pessoas.end(),
                     [](const std::shared_ptr<Pessoa> &a, const std::shared_ptr<Pessoa> &b) {
                         return a->getIdade() > b->getIdade();
                     });
}

bool Emparelhador::posto_disponivel() {
    return std::any_of(postos.begin(), postos.end(), [](const std::shared_ptr<Posto> &p) {
        return !p->cheio();
    });
}