#ifndef FACTOR_H
#define FACTOR_H 1

/*
 * 求所有因子.
 * 包括1和本身.
 */
vector<ll> normal_factor(ll n)
{
	vector<ll> res;
	for (ll fac = 1; fac * fac <= n; ++fac) {
		if (n % fac == 0) {
			res.push_back(fac);
			if (fac ^ n / fac)
				res.push_back(n / fac);
		}
	}
	sort(res.begin(),res.end());
	return res;
}

/*
 * 求素因子, 且分解.
 * 不包括1和本身.
 */
map<ll, ll> prime_factor(ll n)
{
	map<ll,ll> res;
	// 这里可以换成素数表.
	for (ll fac = 2; fac * fac <= n; ++fac) {
		while (n % fac == 0) {
			++res[fac];
			n /= fac;
		}
	}
	if (n ^ 1)
		res[n] = 1;
	return res;
}

#endif
