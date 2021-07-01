//
// Created by Ariel Santos on 30/06/21.
//

#ifndef TP3_PESSOA_H
#define TP3_PESSOA_H

#include <ostream>
#include <vector>
#include <queue>
#include <memory>

#include "Participante.h"
#include "Posto.h"

class Pessoa : public Participante {
public:
    Pessoa(unsigned id, local loc, unsigned idade) : Participante(id, loc), idade(idade) {}

    void inicializar_preferencias(const lista_postos &postos);

    std::shared_ptr<Posto> proxima_preferencia();

    unsigned int getIdade() const;

    friend std::ostream &operator<<(std::ostream &os, const Pessoa &pessoa);

private:
    struct Preferencias {
        Preferencias(const Pessoa &, lista_postos);

        std::shared_ptr<Posto> proxima();

        std::queue<std::shared_ptr<Posto>> preferencias;

        static bool quase_igual(double a, double b);
    };


    const unsigned idade;
    std::unique_ptr<Preferencias> preferencias;
};

typedef std::vector<std::shared_ptr<Pessoa>> lista_pessoas;


#endif //TP3_PESSOA_H
