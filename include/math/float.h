#ifndef FLOAT_H
#define FLOAT_H 1

int fdu(double x)
{
	return fabs(x) < eps ? 0 : x <= -eps ? -1 : 1;
}
// like ecvt, fcvt, gcvt...
double fcut(double x, int xp)
{
	return 1.L * (ll)(x * pow(10, xp)) / pow(10, xp);
}

#endif
