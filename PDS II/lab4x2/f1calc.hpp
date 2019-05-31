#ifndef F1CALC_H
#define F1CALC_H

#include <string>
#include <tuple>
#include "utils.hpp"

using namespace std;

class F1CALC
{
public:
    static std::tuple<int, int, int, int, int> processaEntradas(string sTP, string sTN, string sFP, string sFN, string sTotal);
    static std::tuple<float, float> calculaPresRecall(int TP, int TN, int FP, int FN, int Total);
    static float calculaF1(float p, float r);
};

#endif