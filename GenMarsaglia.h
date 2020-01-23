#pragma once
#include "Gen.h"
class GenMarsaglia : public Gen
{
public:
    GenMarsaglia(int n, double p);
    virtual std::string getName();
    virtual int gen(int n, double p);
private:
    double binomialDeviation;
    double middle;
    GenMarsaglia();
};

