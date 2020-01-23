#pragma once

#include "Gen.h"

typedef struct s_binomial_t {
	int has_binomial; /* !=0: following parameters initialized for binomial */
	double psave;
	int nsave;
	double r;
	double q;
	double fm;
	int m;
	double p1;
	double xm;
	double xl;
	double xr;
	double c;
	double laml;
	double lamr;
	double p2;
	double p3;
	double p4;
} binomial_t;

class GenNumpy : public Gen
{
public:
	GenNumpy();
	~GenNumpy();
	virtual std::string getName();
	virtual int gen(int n, double p);
private:
	binomial_t* p_binomial;
	int random_binomial_inversion(int n, double p); 
	int genBTPE(int n, double p);
};

