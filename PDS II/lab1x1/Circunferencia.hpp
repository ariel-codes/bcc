#define PI 3.14

struct Circunferencia
{
    double xc, yc;
    double raio;

    double calcularArea();
    bool possuiIntersecao(Circunferencia *c);
};