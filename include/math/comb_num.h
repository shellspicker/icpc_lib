#pragma once

template<size_t dn>
struct comb_num_static {
	ull ret[dn + 1][dn + 1];
	comb_num_static(const ull mod = -1) {
		ret[0][0] = 1;
		fup (n, 1, dn) {
			ret[n][0] = ret[n][n] = 1;
			fup (k, 1, n - 1) {
				ret[n][k] = ret[n - 1][k] + ret[n - 1][k - 1];
				if (mod ^ -1)
					ret[n][k] %= mod;
			}
		}
	}
	ull calc(ull n, ull k) {
		return ret[n][k];
	}
};

ull comb_num_calc(ull n, ull k)
{
	if (n < k)
		return 0;
	k = min(k, n - k);
	double ret = 0;
	fwn_range_r (x, n, k)
		ret += log(x);
	fup_range (x, 1, k)
		ret -= log(x);
	return exp(ret) + .5;
}

template<size_t dn>
struct comb_num_mod {
	modulo fac[dn + 1], inv[dn + 1];
	comb_num_mod(ull mod) {
		modulo::mod = mod;
		fac[0] = 1;
		fup (x, 1, dn)
			fac[x] = fac[x - 1] * modulo(x);
		inv[0] = inv[1] = 1;
		fup (x, 2, dn)
			inv[x] = inv[mod % x] * modulo(mod - mod / x);
		fup (x, 1, dn)
			inv[x] = inv[x - 1] * inv[x];
	};
	ull calc(ull n, ull k) {
		return fac[n] * inv[k] * inv[n - k];
	}
};
