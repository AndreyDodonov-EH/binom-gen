#include <random>
#include "GenSTD.h"

GenSTD::GenSTD(int n, double p)
{
    p_distribution = new std::binomial_distribution<int>(n, p);
}

std::string GenSTD::getName()
{
    return "STD";
}

int GenSTD::gen(int n, double p)
{
    const int distr = (*p_distribution)(generator);
    return distr;
}