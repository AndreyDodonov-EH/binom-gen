#pragma once
#include <iostream>
class Gen
{
public:
    virtual void getStatistics(int n, double p, int nrolls, int* const statistics, const int* const refStatistics, long long& duration, double& DKL, bool log);
    virtual std::string getName() = 0;
protected:
    virtual int gen(int n, double p) = 0;
private:
    int getVectorDistance(int* A, int* B, int size);
    double getDivKullbackLeibler(const int* const P, const int* const Q, const int outcomes, const int nrolls);
    double getDKLMirrored(const int* const P, const int* const Q, const int outcomes, const int nrolls);
};

