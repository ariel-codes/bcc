#include <iostream>
#include <string>
#include <fstream>
#include "Indice.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    string content;
    Indice indice;

    while (getline(cin, content))
    {
        if (content.empty())
            break;
        indice.adicionaTexto(content);
    }
    const vector<Indice::palavra> palavras = indice.retornaPalavras3();
    for (vector<Indice::palavra>::const_iterator iter = palavras.begin(); iter != palavras.end(); ++iter)
    {
        printf("%s %d %.2f\n", iter->valor.c_str(), iter->aparicoes, iter->frequencia);
    }

    return 0;
}
