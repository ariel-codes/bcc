//
// Created by Ariel Santos on 30/06/21.
//

#ifndef TP3_POSTO_H
#define TP3_POSTO_H

#include <ostream>
#include <vector>
#include <list>
#include <memory>

#include "Participante.h"

class Pessoa;

class Posto : public Participante {
public:
    Posto(unsigned id, local loc, unsigned cap) : Participante(id, loc), capacidade(cap) {};

    bool cheio() const;

    void alocar(const std::shared_ptr<Pessoa> &Pessoa);

    friend std::ostream &operator<<(std::ostream &os, const Posto &posto);

private:
    const unsigned capacidade;
    std::list<std::shared_ptr<Pessoa>> alocados;
};

typedef std::vector<std::shared_ptr<Posto>> lista_postos;


#endif //TP3_POSTO_H
