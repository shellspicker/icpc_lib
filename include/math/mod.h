#ifndef MOD_H
#define MOD_H 1

#include "math/exgcd.h"

ull mul_mod(ull a, ull b, ull mod)
{
	ull res = (a * b - (ll)(a / (ldb)mod * b + 1e-3) * mod + mod) % mod;
	return res;
}
ll pow_mod(ll x, ll n, ll mod)
{
	if (mod == 1)
		return 0;
	ll res = 1;
	while (n > 0) {
		if (n & 1)
			res = mul_mod(res, x, mod);
		x = mul_mod(x, x, mod);
		n >>= 1;
	}
	return res;
}
class modular {
	ll x;
public:
	static ll mod;
	modular(ll x_) : x(x_) {}
	operator ll() const { return x; }
	modular operator +(const modular &y) const { return modular((x + y) % mod); }
	modular operator -(const modular &y) const { return modular((x - y + mod) % mod); }
	modular operator *(const modular &y) const { return modular(mul_mod(x, y, mod)); }
	modular operator /(const modular &y) const { return *this * y.inverse(); }
	modular operator ^(const modular &y) const { return pow_mod(x, y, mod); }
	modular inverse() const { return modular(mod_inv(x, mod)); }
};
ll modular::mod;

#endif
