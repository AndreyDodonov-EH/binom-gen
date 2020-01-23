#include <random>
#include "GenRef.h"

std::string GenRef::getName()
{
	return "Ref";
}

int GenRef::gen(int n, double p)
{
	int randomVariate = 0;
	for (int i = 0; i <= n; i++)
	{
		double res = ((double)rand() / (RAND_MAX));
		if (res < p)
		{
			randomVariate++;
		}
	}
	return randomVariate;
}
