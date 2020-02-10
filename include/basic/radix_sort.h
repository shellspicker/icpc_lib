template<typename tp>
void radix_sort(vector<tp> &v, uint blk = 1 << 8)
{
	auto counting_sort = [](vector<tp> &v, tp chunk, uint blk) {
		auto bit = [=](tp x) {
			return x >> ctz(chunk) & (blk - 1);
		};
		vector<tp> cnt(blk, 0), cp(v.size());
		for (auto x : v)
			cnt[bit(x)]++;
		partial_sum(it_each(cnt), cnt.begin());
		fwn (i, 0, v.size() - 1) {
			tp &x = v[i];
			cp[--cnt[bit(x)]] = x;
		}
		copy(it_each(cp), v.begin());
	};
	if (std::is_signed<tp>::value) {
		typedef typename std::make_unsigned<tp>::type utp;
		auto is_minus = [](tp x) { return x < 0; };
		vector<utp> cp(v.size());
		copy(it_each(v), cp.begin());
		radix_sort(cp, blk);
		size_t fd = find_if(it_each(cp), is_minus) - cp.begin();
		copy(it_prefix(cp, fd), v.end() - fd);
		copy(it_suffix(cp, fd), v.begin());
	} else {
		tp chunk = 1;
		for (;; chunk <<= ctz(blk)) {
			if (is_sorted(it_each(v)))
				break;
			counting_sort(v, chunk, blk);
			if (chunk << ctz(blk) < chunk)
				break;
		}
	}
}
