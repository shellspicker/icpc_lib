#include "template.h"
#include "basic/radix_sort_test.h"

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
	debug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
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
	debug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
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
	debug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
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
	debug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
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
	debug(is_sorted(v.begin(), v.end()) ? "sorted:" : "unsorted:", (t2 - t1) / 1000);
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
