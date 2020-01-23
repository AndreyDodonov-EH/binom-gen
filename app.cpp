#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <time.h>
#include <chrono>
#include <random>

#include "Gen.h"
#include "GenRef.h"
#include "GenSTD.h"
#include "GenNumpy.h"
#include "GenBoxMueller.h"
#include "GenMarsaglia.h"
#include <map>

std::vector<Gen*> getDistrs(const int n, const double p)
{
    std::vector<Gen*> distrs;
    distrs.push_back(new GenSTD(n, p));
    distrs.push_back(new GenNumpy());
    distrs.push_back(new GenBoxMueller(n, p));
    distrs.push_back(new GenMarsaglia(n, p));
    return distrs;
}

void measure(const int n, const double p, const int nrolls, double* const DKLS, long long* const durations)
{
    const int outcomes = n + 1;
    int* refStatistics{ new int[outcomes] {} };
    GenRef* genRef = new GenRef();
    long long refDuration;
    double refDKL;
    genRef->getStatistics(n, p, nrolls, refStatistics, refStatistics, refDuration, refDKL, false);

    std::vector<Gen*> distrs = getDistrs(n, p);
    int i = 0;
    for (std::vector<Gen*>::iterator it = distrs.begin(); it != distrs.end(); ++it)
    {
        int* statistics{ new int[outcomes] {} };
        long long duration;
        double DKL;
        (*it)->getStatistics(n, p, nrolls, statistics, refStatistics, duration, DKL, false);
        DKLS[i] = DKL;
        durations[i] = duration;
        i++;
        delete[] statistics;

     /*   std::ofstream myfile;
        std::string fileName = "statistics_" + (*it)->getName() + std::to_string(n) + "_" + std::to_string(p) + ".csv";
        myfile.open(fileName);
        for (int i = 0; i <= outcomes; i++)
        {
            myfile << std::to_string(statistics[i]) << "\n";
        }
        myfile.close();*/
    }

    delete[] refStatistics;
}


int main()
{
    srand(time(NULL));
    const int nrolls = 100000;
    const int distrs = 4;

    double* DKLS{ new double[distrs] {} };
    long long* durations{ new long long[distrs] {} };

    std::ofstream fileDKLS;
    fileDKLS.open("DKLs.csv");
    std::ofstream fileDurations;
    fileDurations.open("durations.csv");

    fileDKLS << "N, P, STD, Numpy, BoxMueller, Marsaglia\n";
    fileDurations << "N, P, STD, Numpy, BoxMueller, Marsaglia\n";
    for (int n = 0; n < 1000; n+=100)
    {
        for (double p = 0.0; p <= 0.5; p += 0.05)
        {
            if (n * p <= 30)
            {
                continue;
            }
            std::cout << std::to_string(n) << " " << std::to_string(p) << std::endl;
            measure(n, p, nrolls, DKLS, durations);

            fileDKLS << std::to_string(n) << "," << std::to_string(p) << ","
                << std::to_string(DKLS[0]) << "," << std::to_string(DKLS[1]) << ","
                << std::to_string(DKLS[2]) << "," << std::to_string(DKLS[3]) << "\n";

            fileDurations << std::to_string(n) << "," << std::to_string(p) << ","
                << std::to_string(durations[0]) << "," << std::to_string(durations[1]) << ","
                << std::to_string(durations[2]) << "," << std::to_string(durations[3]) << "\n";
        }
    }
    fileDKLS.close();
    fileDurations.close();

    std::cout << "DONE" << std::endl;
    char x;
    std::cin >> x;
}