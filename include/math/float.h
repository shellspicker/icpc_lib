#pragma once

int fdu(double x)
{
	return fabs(x) < eps ? 0 : x <= -eps ? -1 : 1;
}
// like ecvt, fcvt, gcvt...
double fcut(double x, int xp)
{
	return 1. * (ll)(x * pow(10, xp) + .5) / pow(10, xp);
}
