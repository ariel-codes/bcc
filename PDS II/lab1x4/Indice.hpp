#ifndef INDICE_H
#define INDICE_H

#include <string>
#include <map>
#include <vector>

using namespace std;

struct Indice
{

  private:
    map<string, int> contagem;
    vector<string> palavras;
    void adicionaPalavra(string palavra);

  public:
    struct palavra
    {
        string valor;
        int aparicoes;
        float frequencia;
    };
    vector<palavra> retornaPalavras3();
    double retornaFrequencia(const string &palavra);
    void adicionaTexto(const string &texto);
};

#endif
