#include "f1calc.hpp"

#include <regex>
#include <assert.h>

std::tuple<int, int, int, int, int> F1CALC::processaEntradas(string sTP, string sTN, string sFP, string sFN, string sTotal)
{
    // Dá match em números inteiros
    regex padrao_numero("^[+-]?[[:digit:]]+$");
    string inputs[] = {sTP, sTN, sFP, sFN, sTotal};
    for (int i = 0; i < 5; i++)
    {
        ASSERT(regex_match(inputs[i], padrao_numero), "Input validation failed");
    }
    return tuple(stoi(sTP), stoi(sTN), stoi(sFP), stoi(sFN), stoi(sTotal));
}

std::tuple<float, float> F1CALC::calculaPresRecall(int TP, int TN, int FP, int FN, int Total)
{
    ASSERT(TP >= 0 && TN >= 0 && FP >= 0 && FN >= 0 && Total >= 0 && (TP + TN + FP + FN == Total), "Pre-condition failed");
    return tuple((float)TP / (TP + FP), (float)TP / (FN + TP));
}

float F1CALC::calculaF1(float p, float r)
{
    return 2 * ((p * r) / (p + r));
}