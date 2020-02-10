#ifndef MOD_H
#define MOD_H 1

ull mul_mod(ull a, ull b, ull mod)
{
	ull res = (a * b - (ll)(a / (ldb)mod * b + 1e-3) * mod + mod) % mod;
	return res;
}
template<typename tp>
tp pow_mod(tp x, tp n, tp mod)
{
	if (mod == 1)
		return 0;
	tp res = 1;
	while (n > 0) {
		if (n & 1)
			res = mul_mod(res, x, mod);
		x = mul_mod(x, x, mod);
		n >>= 1;
	}
	return res;
}

#endif