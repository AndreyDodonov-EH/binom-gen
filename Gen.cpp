#include "Gen.h"
#include <chrono>

void Gen::getStatistics(int n, double p, int nrolls, int* const statistics, const int* const refStatistics, long long& duration, double& DKL, bool log)
{
	const int outcomes = n + 1;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for (int i = 0; i < nrolls; ++i) {
		int number = gen(n, p);
		++statistics[number];
	}
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
	DKL = getDKLMirrored(statistics, refStatistics, outcomes, nrolls);

	if (log) std::cout << duration << "\t[micros]" << "\tDKL " << DKL << std::endl;
}

int Gen::getVectorDistance(int* A, int* B, int size)
{
	int dist = 0;
	for (int i = 0; i < size; i++)
	{
		dist += (B[i] - A[i]) * (B[i] - A[i]);
	}
	return (int)sqrt(dist);
}

double Gen::getDivKullbackLeibler(const int* const P, const int* const Q, const int outcomes, const int nrolls)
{
	double DKL = 0;
	for (int i = 0; i < outcomes; i++)
	{
		if ((Q[i] == 0) || P[i] == 0)
			continue;
		const double p = double(P[i]) / nrolls;
		const double q = double(Q[i]) / nrolls;
		DKL += p * log(p / q);
	}
	return DKL;
}

double Gen::getDKLMirrored(const int* const P, const int* const Q, const int outcomes, const int nrolls)
{
	return getDivKullbackLeibler(P, Q, outcomes, nrolls) + getDivKullbackLeibler(Q, P, outcomes, nrolls);
}