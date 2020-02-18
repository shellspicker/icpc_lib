#ifndef CRT_H
#define CRT_H 1

#include "math/exgcd.h"
#include "math/gcd_lcm.h"

pair<ll, ll> crt(ll x1, ll m1, ll x2, ll m2)
{
	if (m1 < m2)
		return crt(x2, m2, x1, m1);
	ll x, y, g = exgcd(m1, m2, x, y);
	assert((x1 - x2) % g == 0);
	x = (x2 - x1) % m2 * x % m2 / g * m1 + x1;
	return {(x < 0 ? x + lcm(m1, m2) : x), lcm(m1, m2)};
}

#endif
