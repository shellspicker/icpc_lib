#pragma once

/*
 * rmq.
 * 宏: STEP.
 *
 * STEP:
 * 下标跳跃.
 */

template<
	typename tp>
class rmq {
	using fn_comb = function<tp(tp, tp)>;
	vector<vector<tp>> ds;
#if STEP
	vector<vector<int>> step;
#endif
public:
	fn_comb comb;
#if STEP
	rmq(fn_comb fn, const vector<int> &nxt) {
		comb = fn;
		step = double_scale(nxt);
	}
#else
	rmq(fn_comb fn) { comb = fn; }
#endif
	void init(const vector<tp> &v) {
		int sz, xp;
		sz = v.size();
		xp = half2xp(sz);
		ds.resize(xp + 1);
		ds[0].assign(it_each(v));
		fup (b, 1, xp) {
			ds[b].resize(sz);
#if STEP
			fup_range (s, 0, sz)
				if (~step[b - 1][s])
					ds[b][s] = comb(
							ds[b - 1][s],
							ds[b - 1][step[b - 1][s]]);
#else
			for (int s = 0, t; (t = ltor(s, (1 << b))) < sz; ++s)
				ds[b][s] = comb(
						ds[b - 1][s],
						ds[b - 1][midpoint(s, t)]);
#endif
		}
	}
	tp query(int l, int r) {
		assert(l <= r);
		int xp, len;
		xp = half2xp(length(l, r));
		len = 1 << xp;
		return comb(ds[xp][l], ds[xp][rtol(r, len)]);
	}
};

#undef STEP
