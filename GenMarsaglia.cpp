#include <corecrt_math_defines.h>
#include <random>
#include "GenMarsaglia.h"

GenMarsaglia::GenMarsaglia(int n, double p) : Gen()
{
	binomialDeviation = sqrt(n * p * (1 - p));
	middle = p * n;
}

std::string GenMarsaglia::getName()
{
	return "Marsaglia";
}

int GenMarsaglia::gen(int n, double p)
{
	double s = 0;
	double u;
	do
	{
		double u1 = ((double)rand() / (RAND_MAX));
		double u2 = ((double)rand() / (RAND_MAX));
		u = 2.0 * u1 - 1.0;
		double v = 2.0 * u2 - 1.0;
		s = u * u + v * v;
	} while (s >= 1);

	double rand_std_normal = u * sqrt(-2.0 * log(s) / s);
	double rand_normal = middle + binomialDeviation * rand_std_normal;

	return static_cast<int>(std::round(rand_normal));
}