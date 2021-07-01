//
// Created by Ariel Santos on 30/06/21.
//

#ifndef TP3_LOCALIZACAO_H
#define TP3_LOCALIZACAO_H


#include <ostream>

class Localizacao {
public:
    Localizacao(unsigned x, unsigned y) : x(x), y(y) {};

    double distancia(Localizacao) const;

    friend std::ostream &operator<<(std::ostream &os, const Localizacao &localizacao);

private:
    const int x, y;
};

typedef Localizacao local;

#endif //TP3_LOCALIZACAO_H
