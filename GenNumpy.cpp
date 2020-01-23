#include "GenNumpy.h"
#include <algorithm>
#include <string>

GenNumpy::GenNumpy()
{
	p_binomial = new binomial_t();
	p_binomial->has_binomial = 0;
}

GenNumpy::~GenNumpy()
{
	delete p_binomial;
}

std::string GenNumpy::getName()
{
	return "Numpy";
}

int GenNumpy::gen(int n, double p)
{
	if (p * n <= 30)
	{
		return random_binomial_inversion(n, p);
	}
	else
	{
		return genBTPE(n, p);
	}
}

int GenNumpy::random_binomial_inversion(int n, double p)
{
	double q, qn, np, px, U;
	int X, bound;

	if (!(p_binomial->has_binomial) || (p_binomial->nsave != n) ||
		(p_binomial->psave != p)) {
		p_binomial->nsave = n;
		p_binomial->psave = p;
		p_binomial->has_binomial = 1;
		p_binomial->q = q = 1.0 - p;
		p_binomial->r = qn = exp(n * log(q));
		p_binomial->c = np = n * p;
		p_binomial->m = bound = (int)std::min(double(n), np + 10.0 * sqrt(np * q + 1));
	}
	else {
		q = p_binomial->q;
		qn = p_binomial->r;
		np = p_binomial->c;
		bound = p_binomial->m;
	}
	X = 0;
	px = qn;
	do
		U = (double)rand() / RAND_MAX;
	while (U == 0.0);
	while (U > px) {
		X++;
		if (X > bound) {
			X = 0;
			px = qn;
			do
				U = (double)rand() / RAND_MAX;
			while (U == 0.0);
		}
		else {
			U -= px;
			px = ((n - X + 1) * p * px) / (X * q);
		}
	}
	return X;
}

int GenNumpy::genBTPE(int n, double p)
{
	double r, q, fm, p1, xm, xl, xr, c, laml, lamr, p2, p3, p4;
	double a, u, v, s, F, rho, t, A, nrq, x1, x2, f1, f2, z, z2, w, w2, x;
	int m, y, k, i;

	if (!(p_binomial->has_binomial) || (p_binomial->nsave != n) ||
		(p_binomial->psave != p)) {
		/* initialize */
		p_binomial->nsave = n;
		p_binomial->psave = p;
		p_binomial->has_binomial = 1;
		p_binomial->r = r = std::min(p, 1.0 - p);
		p_binomial->q = q = 1.0 - r;
		p_binomial->fm = fm = n * r + r;
		p_binomial->m = m = (int)floor(p_binomial->fm);
		p_binomial->p1 = p1 = floor(2.195 * sqrt(n * r * q) - 4.6 * q) + 0.5;
		p_binomial->xm = xm = m + 0.5;
		p_binomial->xl = xl = xm - p1;
		p_binomial->xr = xr = xm + p1;
		p_binomial->c = c = 0.134 + 20.5 / (15.3 + m);
		a = (fm - xl) / (fm - xl * r);
		p_binomial->laml = laml = a * (1.0 + a / 2.0);
		a = (xr - fm) / (xr * q);
		p_binomial->lamr = lamr = a * (1.0 + a / 2.0);
		if (lamr == 0.0)
		{
			int x = 0;
		}
		p_binomial->p2 = p2 = p1 * (1.0 + 2.0 * c);
		p_binomial->p3 = p3 = p2 + c / laml;
		p_binomial->p4 = p4 = p3 + c / lamr;
	}
	else {
		r = p_binomial->r;
		q = p_binomial->q;
		fm = p_binomial->fm;
		m = p_binomial->m;
		p1 = p_binomial->p1;
		xm = p_binomial->xm;
		xl = p_binomial->xl;
		xr = p_binomial->xr;
		c = p_binomial->c;
		laml = p_binomial->laml;
		lamr = p_binomial->lamr;
		p2 = p_binomial->p2;
		p3 = p_binomial->p3;
		p4 = p_binomial->p4;
	}

	/* sigh ... */
Step10:
	nrq = n * r * q;
	u = (double)rand() / RAND_MAX * p4;
	do
		v = (double)rand() / RAND_MAX;
	while (v == 0.0);
	if (u > p1)
		goto Step20;
	y = (int)floor(xm - p1 * v + u);
	goto Step60;

Step20:
	if (u > p2)
		goto Step30;
	x = xl + (u - p1) / c;
	v = v * c + 1.0 - fabs(m - x + 0.5) / p1;
	if (v > 1.0)
		goto Step10;
	y = (int)floor(x);
	goto Step50;

Step30:
	if (u > p3)
		goto Step40;
	y = (int)floor(xl + log(v) / laml);
	/* Reject if v==0.0 since previous cast is undefined */
	if ((y < 0) || (v == 0.0))
		goto Step10;
	v = v * (u - p2) * laml;
	goto Step50;

Step40:
	y = (int)floor(xr - log(v) / lamr);
	/* Reject if v==0.0 since previous cast is undefined */
	if ((y > n) || (v == 0.0))
		goto Step10;
	v = v * (u - p3) * lamr;

Step50:
	k = llabs(y - m);
	if ((k > 20) && (k < ((nrq) / 2.0 - 1)))
		goto Step52;

	s = r / q;
	a = s * (n + 1);
	F = 1.0;
	if (m < y) {
		for (i = m + 1; i <= y; i++) {
			F *= (a / i - s);
		}
	}
	else if (m > y) {
		for (i = y + 1; i <= m; i++) {
			F /= (a / i - s);
		}
	}
	if (v > F)
		goto Step10;
	goto Step60;

Step52:
	rho =
		(k / (nrq)) * ((k * (k / 3.0 + 0.625) + 0.16666666666666666) / nrq + 0.5);
	t = -k * k / (2 * nrq);
	/* log(0.0) ok here */
	A = log(v);
	if (A < (t - rho))
		goto Step60;
	if (A > (t + rho))
		goto Step10;

	x1 = y + 1;
	f1 = m + 1;
	z = n + 1 - m;
	w = n - y + 1;
	x2 = x1 * x1;
	f2 = f1 * f1;
	z2 = z * z;
	w2 = w * w;
	if (A > (xm * log(f1 / x1) + (n - m + 0.5) * log(z / w) +
		(y - m) * log(w * r / (x1 * q)) +
		(13680. - (462. - (132. - (99. - 140. / f2) / f2) / f2) / f2) / f1 /
		166320. +
		(13680. - (462. - (132. - (99. - 140. / z2) / z2) / z2) / z2) / z /
		166320. +
		(13680. - (462. - (132. - (99. - 140. / x2) / x2) / x2) / x2) / x1 /
		166320. +
		(13680. - (462. - (132. - (99. - 140. / w2) / w2) / w2) / w2) / w /
		166320.)) {
		goto Step10;
	}

Step60:
	if (p > 0.5) {
		y = n - y;
	}

	return y;
}