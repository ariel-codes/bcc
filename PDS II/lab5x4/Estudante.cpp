#include "Estudante.hpp"

bool Estudante::determinarAprovacao(double notaFinal, double notaEspecial, double frequencia)
{
    if (notaFinal > 100 || notaEspecial > 100 || frequencia > 1.0 || notaFinal < 0 || notaEspecial < 0 || frequencia < 0)
        throw ErroDeterminarAprovacao();

    // Conceito F
    if (frequencia < 0.75 || notaFinal < 40)
        return false;

    // Conceito D - A
    if (notaFinal >= 60)
        return true;

    // Conceito E
    if (((notaEspecial + notaFinal) / 2) >= 60)
        return true;

    return false;
}