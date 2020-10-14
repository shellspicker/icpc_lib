#pragma once

#if FUNC_HASH
#  define STEP 1
#endif

/*
 * rmq.
 * 宏: STEP, FUNC_HASH.
 *
 * STEP:
 * 下标跳跃.
 *
 * FUNC_HASH:
 * 求hash, 然后可以查询2个位置的lcp和字典序关系.
 * 这里只写了计蒜客a1401的跳跃下标查询.
 */
#if FUNC_HASH
template<
	typename tp = ull,
	class fn_cmp = less<tp>,
	tp seed = 131>
#else
template<
	typename tp>
#endif
class rmq {
	using fn_comb = function<tp(tp, tp)>;
	vector<vector<tp>> ds;
#if STEP
	vector<vector<int>> step;
#endif
public:
	fn_comb comb;
#if FUNC_HASH
	fn_cmp cmp = func_cmp();
	vector<tp> exp;// seed ^ (2 ^ n).
#endif
#if STEP
	rmq(const vector<int> &nxt) {
		step = double_scale(nxt);
	}
#else
	rmq() {}
#endif
	void set_comb(fn_comb fp) {
		comb = fp;
	}
	void init(const vector<tp> &v) {
		int sz, xp;
		sz = v.size();
		xp = half2xp(sz);
		ds.resize(xp + 1);
		ds[0].assign(it_each(v));
#if FUNC_HASH
		exp.resize(xp + 1);
		exp[0] = seed;// seed ^ (2 ^ 0);
		fup (x, 1, xp)
			exp[x] = exp[x - 1] * exp[x - 1];
#endif
		fup (b, 1, xp) {
			ds[b].resize(sz);
#if STEP
			fup_range (s, 0, sz)
				if (~step[b - 1][s])
#  if FUNC_HASH
					ds[b][s] = comb(
							ds[b - 1][s] * exp[b - 1],
							ds[b - 1][step[b - 1][s]]);
#  else
					ds[b][s] = comb(
							ds[b - 1][s],
							ds[b - 1][step[b - 1][s]]);
#  endif
#else
			for (int s = 0, t; (t = ltor(s, (1 << b))) < sz; ++s)
				ds[b][s] = comb(
						ds[b - 1][s],
						ds[b - 1][midpoint(s, t)]);
#endif
		}
	}
#if FUNC_HASH
	bool range_query(int l, int r) {
		int xp, len;
		xp = ds.size() - 1;
		len = ds[0].size();
		while (xp--) {
			int half = 1 << xp;// alredy half length.
			if (half <= len && ds[xp][l] == ds[xp][r]) {
				// assume l and r will not extend out of range.
				l = step[xp][l];
				r = step[xp][r];
				len -= half;
			}
		}
		if (!len)
			return 0;
		else
			return cmp(ds[0][l], ds[0][r]);
	}
#else
	tp range_query(int l, int r) {
		assert(l <= r);
		int xp, len;
		xp = half2xp(length(l, r));
		len = 1 << xp;
		return comb(ds[xp][l], ds[xp][rtol(r, len)]);
	}
#endif
};

#undef STEP
#undef FUNC_HASH
