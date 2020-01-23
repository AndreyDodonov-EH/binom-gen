#pragma once
#include "Gen.h"
class GenBoxMueller : public Gen
{
public:
    GenBoxMueller(int n, double p);
    virtual std::string getName();
    virtual int gen(int n, double p);
private:
    double binomialDeviation;
    double middle;
    GenBoxMueller();
};

