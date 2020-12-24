template<typename tp>
void radix_sort_bucket_normal(vector<tp> &v, uint blk = 1 << 8)
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
		radix_sort_bucket_normal(cp, blk);
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
template<typename tp>
void radix_sort_bucket_divide(vector<tp> &v, uint blk = 1 << 8)
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
		size_t sz = count_if(it_each(v), is_minus);
		vector<utp> ne(sz), po(v.size() - sz);
		copy_if(it_each(v), ne.begin(), is_minus);
		remove_copy_if(it_each(v), po.begin(), is_minus);
		radix_sort_bucket_divide(ne, blk);
		radix_sort_bucket_divide(po, blk);
		copy(it_each(ne), v.begin());
		copy(it_each(po), v.begin() + sz);
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
template<typename tp>
void radix_sort_list_normal(vector<tp> &v, uint blk = 1 << 8)
{
	if (std::is_signed<tp>::value) {
		typedef typename std::make_unsigned<tp>::type utp;
		auto is_minus = [](tp x) { return x < 0; };
		vector<utp> cp(v.size());
		copy(it_each(v), cp.begin());
		radix_sort_list_normal(cp, blk);
		size_t fd = find_if(it_each(cp), is_minus) - cp.begin();
		copy(it_prefix(cp, fd), v.end() - fd);
		copy(it_suffix(cp, fd), v.begin());
	} else {
		vector<vector<tp>> radix(blk);
		vector<tp> all;
		tp chunk = 1;
		for (auto x : v)
			all.emplace_back(x);
		for (;; chunk <<= ctz(blk)) {
			if (is_sorted(it_each(v)))
				break;
			for (auto x : all)
				radix[x >> ctz(chunk) & (blk - 1)].emplace_back(x);
			all.clear();
			for (auto &cur : radix) {
				if (!cur.empty()) {
					for (auto x : cur)
						all.emplace_back(x);
					cur.clear();
				}
			}
			if (chunk << ctz(blk) < chunk)
				break;
		}
		copy(all.begin(), all.end(), v.begin());
	}
}
template<typename tp>
void radix_sort_list_divide(vector<tp> &v, uint blk = 1 << 8)
{
	if (std::is_signed<tp>::value) {
		typedef typename std::make_unsigned<tp>::type utp;
		auto is_minus = [](tp x) { return x < 0; };
		size_t sz = count_if(it_each(v), is_minus);
		vector<utp> ne(sz), po(v.size() - sz);
		copy_if(it_each(v), ne.begin(), is_minus);
		remove_copy_if(it_each(v), po.begin(), is_minus);
		radix_sort_list_divide(ne, blk);
		radix_sort_list_divide(po, blk);
		copy(it_each(ne), v.begin());
		copy(it_each(po), v.begin() + sz);
	} else {
		vector<vector<tp>> radix(blk);
		vector<tp> all;
		tp chunk = 1;
		for (auto x : v)
			all.emplace_back(x);
		for (;; chunk <<= ctz(blk)) {
			if (is_sorted(it_each(v)))
				break;
			for (auto x : all)
				radix[x >> ctz(chunk) & (blk - 1)].emplace_back(x);
			all.clear();
			for (auto &cur : radix) {
				if (!cur.empty()) {
					for (auto x : cur)
						all.emplace_back(x);
					cur.clear();
				}
			}
			if (chunk << ctz(blk) < chunk)
				break;
		}
		copy(all.begin(), all.end(), v.begin());
	}
}

