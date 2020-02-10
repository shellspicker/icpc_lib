#ifndef RMQ_H
#define RMQ_H 1

template<typename tp, bool is_min>
class rmq {
	vector<tp> ds[20];
public:
	void init(const vector<tp> &v) {
		int sz = v.size();
		for (auto &dim : ds)
			dim.resize(sz);
		fup (i, 0, sz - 1)
			ds[0][i] = v[i];
		for (int b = 1; (1 << b) <= sz; ++b)
			for (int s = 0; s + (1 << b) <= sz; ++s) {
				if (is_min)
					ds[b][s] = min(ds[b - 1][s], ds[b - 1][s + (1 << b - 1)]);
				else
					ds[b][s] = max(ds[b - 1][s], ds[b - 1][s + (1 << b - 1)]);
			}
	}
	tp query(int l, int r) {
		range_normalize(l, r);
		tp xp = ctz(rounddown_pow_of_2(length(l, r)));
		if (is_min)
			return min(ds[xp][l], ds[xp][rtol(r, 1 << xp)]);
		else
			return max(ds[xp][l], ds[xp][rtol(r, 1 << xp)]);
	}
};

#endif
