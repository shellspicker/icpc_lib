vector<int> prime_sieve(ll n)
{
	vector<bool> rm(n + 1);
	vector<int> pri;
	int bsz = max(3, int(ceil(sqrt(n))));
	rm[1] = 1;
	fup (fac, 2, bsz) if (!rm[fac])
		for (ll g = 1ll * fac * fac; g <= n; g += fac)
			rm[g] = 1;
	fup (x, 2, n) if (!rm[x])
		pri.push_back(x);
	return pri;
}

class sieve {
public:
	vector<bool> rm;
	vector<int> pri;
	sieve(int n) {
		rm.resize(n + 1);
		rm[1] = 1;
	}
	void run() {
		int n = rm.size() - 1;
		fup (x, 2, n) {
			if (!rm[x]) {
				prime_init(x);
				pri.push_back(x);
			}
			for (auto &m1 : pri) {
				int nopri = m1 * x;
				if (n < nopri)
					break;
				rm[nopri] = 1;
				if (x % m1 == 0) {
					same(m1, x);
					break;
				}
				diff(m1, x);
			}
		}
	}
	virtual void prime_init(int x) {}
	virtual void diff(int m1, int x) {}
	virtual void same(int m1, int x) {}
};

class factor_sum : public sieve {
public:
	vector<int> sum, m1p;
	factor_sum(int n) : sieve(n) {
		sum.resize(n + 1);
		m1p.resize(n + 1);
		sum[1] = 1;
		m1p[1] = 1;
	}
	void prime_init(int x) {
		sum[x] = x + 1;
		m1p[x] = x + 1;
	}
	void diff(int m1, int x) {
		int nopri = m1 * x;
		sum[nopri] = sum[m1] * sum[x];
		m1p[nopri] = m1 + 1;
	}
	void same(int m1, int x) {
		int nopri = m1 * x;
		m1p[nopri] = m1p[x] * m1 + 1;
		sum[nopri] = sum[x] / m1p[x] * m1p[nopri];
	}
};

