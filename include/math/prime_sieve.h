#pragma once

vector<int> prime_sieve(ll n)
{
	vector<int> ret;
	vector<bool> rm(n + 1, 0);
	int bsz = max(3, int(ceil(sqrt(n))));
	rm[1] = 1;
	fup (fac, 2, bsz) if (!rm[fac])
		for (ll g = 1ll * fac * fac; g <= n; g += fac)
			rm[g] = 1;
	fup (x, 2, n) if (!rm[x])
		ret.push_back(x);
	return ret;
}
