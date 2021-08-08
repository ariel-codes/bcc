//
// Created by Ariel Santos on 07/08/21.
//

#ifndef TP1_AEROPORTO_H
#define TP1_AEROPORTO_H

#include <memory>
#include <vector>

class Aeroporto;

typedef std::shared_ptr<Aeroporto> AeroportoPtr;

class Aeroporto {
public:
    void add_destino(const AeroportoPtr &);

private:
    std::vector<AeroportoPtr> destinos;
};


#endif //TP1_AEROPORTO_H
