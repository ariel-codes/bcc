#include <iostream>
#include "Circunferencia.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Circunferencia c = {.xc = 2, .yc = 3, .raio = 12};
    Circunferencia c2 = {.xc = 15, .yc = 8, .raio = 10};
    cout << (c.possuiIntersecao(&c2) ? "INTERCEDE" : "NÃO") << endl;
    return 0;
}
