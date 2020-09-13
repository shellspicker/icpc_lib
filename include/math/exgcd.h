#pragma once

#define FAST 1
ll exgcd(ll a, ll b, ll &x, ll &y)
{
#if FAST
	if (a < b)
		return exgcd(b, a, y, x);
	ll m = 0, n = 1;
	x = 1, y = 0;
	while (b) {
		ll d = a / b;
		swap(x, m); m = m - d * x;
		swap(y, n); n = n - d * y;
		a %= b; swap(a, b);
	}
	return a;
#else
	if (b) {
		ll d = exgcd(b, a % b, y, x);
		return y -= a / b * x, d;
	}
	return x = 1, y = 0, a;
#endif
}
#undef FAST

ll mod_inv(ll a, ll b)
{
	ll x, y;
	if (exgcd(a, b, x, y) == 1) {
		x %= b;
		return x < 0 ? x + b : x;
	} else {
		return -1;
	}
}
