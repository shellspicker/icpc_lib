template<typename tp>
struct precalc_sum_op {
	using fn = function<tp(tp, tp)>;
	tp null = tp(0);
	fn comb = plus<tp>();
	fn split = minus<tp>();
};

template<typename tp>
struct precalc_mul_op {
	using fn = function<tp(tp, tp)>;
	tp null = tp(1);
	fn comb = multiplies<tp>();
	fn split = divides<tp>();
};

// TODO: precalc(tp *, int)

template<typename tp, typename policy = precalc_sum_op<tp>>
struct precalc {
#define normal(l, r) \
	if (!~l && !~r) \
		l = 0, r = src.size() - 1
#define fail(l, r) \
	assert(~l && ~r)
#define chk(l, r) \
	normal(l, r); fail(l, r)

	vector<tp> dest;
	const vector<tp> &src;
	policy op;

	precalc(const vector<tp> &v) : src(v) {}
	void add(int l = -1, int r = -1, int st = 0, int m1 = -1, int m2 = -1) {
		chk(l, r);
		chk(m1, m2);
		int len = length(l, r);
		if (dest.size() < st + len)
			dest.resize(st + len);
		for (int di = st, si = l; si <= r; ++si, ++di)
			dest[di] = op.comb(special(op.null, dest, di - 1, m1, m2), src[si]);
	}
	tp get(int l = -1, int r = -1, int m1 = -1, int m2 = -1) {
		chk(l, r);
		chk(m1, m2);
		return op.split(dest[r], special(op.null, dest, l - 1, m1, m2));
	}
#undef normal
#undef fail
#undef chk
};

