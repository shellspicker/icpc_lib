#include "template.h"
#include "basic/rand.h"
debuger bug;

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

template<typename tp>
void test_bucket_normal(int sz, int d, tp m1, tp m2)
{
	vector<tp> v(sz);
	double t1, t2;
	random_int<tp> rd;
	rd.set(m1, m2);
	fup (i, 0, sz - 1)
		v[i] = rd();
	t1 = clock();
	radix_sort_bucket_normal(v, 1 << d);
	t2 = clock();
	bug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
}
template<typename tp>
void test_bucket_divide(int sz, int d, tp m1, tp m2)
{
	vector<tp> v(sz);
	double t1, t2;
	random_int<tp> rd;
	rd.set(m1, m2);
	fup (i, 0, sz - 1)
		v[i] = rd();
	t1 = clock();
	radix_sort_bucket_divide(v, 1 << d);
	t2 = clock();
	bug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
}
template<typename tp>
void test_list_normal(int sz, int d, tp m1, tp m2)
{
	vector<tp> v(sz);
	double t1, t2;
	random_int<tp> rd;
	rd.set(m1, m2);
	fup (i, 0, sz - 1)
		v[i] = rd();
	t1 = clock();
	radix_sort_list_normal(v, 1 << d);
	t2 = clock();
	bug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
}
template<typename tp>
void test_list_divide(int sz, int d, tp m1, tp m2)
{
	vector<tp> v(sz);
	double t1, t2;
	random_int<tp> rd;
	rd.set(m1, m2);
	fup (i, 0, sz - 1)
		v[i] = rd();
	t1 = clock();
	radix_sort_list_divide(v, 1 << d);
	t2 = clock();
	bug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
}
template<typename tp>
void test_std(int sz, tp m1, tp m2)
{
	vector<tp> v(sz);
	double t1, t2;
	random_int<tp> rd;
	rd.set(m1, m2);
	fup (i, 0, sz - 1)
		v[i] = rd();
	t1 = clock();
	sort(v.begin(), v.end());
	t2 = clock();
	bug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
}
void test()
{
	srand(time(0));
	const int sz = 5000000;
	for (auto d : {5, 8, 10}) {
		cout << "\nshift: " << d << endl;
		cout << "bucket normal\n";
		test_bucket_normal<int>(sz, d, -1e9, 1e9);
		test_bucket_normal<uint>(sz, d, 0, ~0u);
		test_bucket_normal<ll>(sz, d, -1e18, 1e18);
		test_bucket_normal<ull>(sz, d, 0ull, ~0ull);
		cout << "bucket divide\n";
		test_bucket_divide<int>(sz, d, -1e9, 1e9);
		test_bucket_divide<uint>(sz, d, 0, ~0u);
		test_bucket_divide<ll>(sz, d, -1e18, 1e18);
		test_bucket_divide<ull>(sz, d, 0ull, ~0ull);
		cout << "list normal\n";
		test_list_normal<int>(sz, d, -1e9, 1e9);
		test_list_normal<uint>(sz, d, 0, ~0u);
		test_list_normal<ll>(sz, d, -1e18, 1e18);
		test_list_normal<ull>(sz, d, 0ull, ~0ull);
		cout << "list divide\n";
		test_list_divide<int>(sz, d, -1e9, 1e9);
		test_list_divide<uint>(sz, d, 0, ~0u);
		test_list_divide<ll>(sz, d, -1e18, 1e18);
		test_list_divide<ull>(sz, d, 0ull, ~0ull);
	}
	cout << "\nstd\n";
	test_std<int>(sz, -1e9, 1e9);
	test_std<uint>(sz, 0, ~0u);
	test_std<ll>(sz, -1e18, 1e18);
	test_std<ull>(sz, 0ull, ~0ull);
}

int main()
{
	test();
	return 0;
}
