#include "Indice.hpp"

using namespace std;

void Indice::adicionaPalavra(string palavra)
{
    palavras.push_back(palavra);
    if (palavra.length() > 2)
        contagem[palavra] += 1;
}

void Indice::adicionaTexto(const string &texto)
{
    string word = "";
    for (string::size_type i = 0; i < texto.size(); ++i)
    {
        if (texto[i] == ' ')
        {
            if (word.size() == 0)
                continue;
            else
            {
                adicionaPalavra(word);
                word.clear();
            }
        }
        else
        {
            word += tolower(texto[i]);
        }
    }
    if (word.size() > 0)
    {
        adicionaPalavra(word);
    }
}

vector<Indice::palavra> Indice::retornaPalavras3()
{
    vector<Indice::palavra> filtrado;
    for (map<string, int>::iterator iter = contagem.begin(); iter != contagem.end(); ++iter)
    {
        Indice::palavra p;
        p.valor = iter->first;
        p.aparicoes = iter->second;
        p.frequencia = retornaFrequencia(p.valor);
        filtrado.push_back(p);
    }
    return filtrado;
}

double Indice::retornaFrequencia(const string &palavra)
{
    const float total = palavras.size(), num = contagem[palavra];
    return num / total;
}
