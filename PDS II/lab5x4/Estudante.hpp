#ifndef ESTUDANTE_INCLUDED
#define ESTUDANTE_INCLUDED
#include <exception>

class Estudante
{
public:
    static bool determinarAprovacao(double, double, double);
};

class ErroDeterminarAprovacao : public std::exception
{
    using std::exception::exception;
};

#endif