#pragma once
#include "Gen.h"
class GenRef :public Gen
{
    virtual std::string getName();
    virtual int gen(int n, double p);
};

