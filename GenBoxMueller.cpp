#include <corecrt_math_defines.h>
#include <random>
#include "GenBoxMueller.h"

GenBoxMueller::GenBoxMueller(int n, double p) : Gen()
{
	binomialDeviation = sqrt(n * p * (1 - p));
	middle = p * n;
}

std::string GenBoxMueller::getName()
{
	return "BoxMueller";
}

int GenBoxMueller::gen(int n, double p)
{
	double u1 = 0.0;
	double u2 = 0.0;
	do
		u1 = ((double)rand() / (RAND_MAX));
	while (u1 == 0.0); // workaround for getting exactly zero
	do
		u2 = ((double)rand() / (RAND_MAX));
	while (u2 == 0.0); // workaround for getting exactly zero
	double rand_std_normal = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);
	double rand_normal = middle + binomialDeviation * rand_std_normal;
	//rand_normal = rand_normal + 0.5 - (rand_normal < 0);
	return static_cast<int>(std::round(rand_normal));
}
