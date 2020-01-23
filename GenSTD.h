#pragma once
#include "Gen.h"

class GenSTD : public Gen
{
public:
    GenSTD(int n, double p);
    virtual std::string getName();
    virtual int gen(int n, double p);

private:
    std::default_random_engine generator;
    std::binomial_distribution<int>* p_distribution;
};

