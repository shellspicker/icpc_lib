template<typename tp>
class rmq {
#define fn min
	vector<tp> ds[20];
public:
	void init(const vector<tp> &v) {
		int sz = v.size();
		for (auto &dim : ds)
			dim.resize(sz);
		fup (i, 0, sz - 1)
			ds[0][i] = v[i];
		for (int b = 1; (1 << b) <= sz; ++b)
			for (int s = 0; s + (1 << b) <= sz; ++s)
				ds[b][s] = fn(ds[b - 1][s], ds[b - 1][s + (1 << b - 1)]);
	}
	tp query(int l, int r) {
		range_normalize(l, r);
		tp xp = ctz(rounddown_pow_of_2(length(l, r)));
		return fn(ds[xp][l], ds[xp][rtol(r, 1 << xp)]);
	}
#undef fn
};