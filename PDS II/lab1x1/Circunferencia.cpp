#include <cmath>
#include "Circunferencia.hpp"

using namespace std;

double Circunferencia::calcularArea()
{
    return PI * pow(raio, 2);
}

bool Circunferencia::possuiIntersecao(Circunferencia *c)
{
    const double distance = sqrt(pow(xc - c->xc, 2) + pow(yc - c->yc, 2));
    return raio + c->raio >= distance;
}
