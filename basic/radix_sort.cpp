#pragma GCC optimize("Ofast")
#pragma GCC target("sse4")
#include <cstddef>
#include <cstdint>
#include <climits>
#include <cstdlib>
#include <cstdarg>
#include <cassert>
#include <cctype>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <bitset>
#include <tr2/dynamic_bitset>
using std::ios;
using std::ios_base;
using std::istream;
using std::ostream;
using std::stringstream;
using std::cin;
using std::cout;
using std::string;
using std::move;
using std::forward;
using std::tuple;
using std::tie;
using std::get;
using std::pair;
using std::vector;
using std::deque;
using std::list;
using std::stack;
using std::queue;
using std::bitset;
using std::tr2::dynamic_bitset;
using std::set;
using std::map;
using std::multiset;
using std::multimap;
using std::unordered_set;
using std::unordered_map;
using std::unordered_multiset;
using std::unordered_multimap;
using std::initializer_list;
using std::all_of;
using std::any_of;
using std::none_of;
using std::for_each;
using std::count;
using std::count_if;
using std::mismatch;
using std::find;
using std::find_if;
using std::find_if_not;
using std::find_end;
using std::find_first_of;
using std::adjacent_find;
using std::search;
using std::search_n;
using std::copy;
using std::copy_if;
using std::copy_n;
using std::copy_backward;
using std::move;
using std::move_backward;
using std::fill;
using std::fill_n;
using std::transform;
using std::generate;
using std::generate_n;
using std::remove;
using std::remove_if;
using std::remove_copy;
using std::remove_copy_if;
using std::replace;
using std::replace_if;
using std::replace_copy;
using std::replace_copy_if;
using std::swap;
using std::swap_ranges;
using std::iter_swap;
using std::reverse;
using std::reverse_copy;
using std::rotate;
using std::rotate_copy;
using std::shuffle;
using std::unique;
using std::unique_copy;
using std::is_partitioned;
using std::partition;
using std::partition_copy;
using std::stable_partition;
using std::partition_point;
using std::is_sorted;
using std::is_sorted_until;
using std::sort;
using std::partial_sort;
using std::partial_sort_copy;
using std::stable_sort;
using std::nth_element;
using std::lower_bound;
using std::upper_bound;
using std::binary_search;
using std::equal_range;
using std::merge;
using std::inplace_merge;
using std::includes;
using std::set_difference;
using std::set_intersection;
using std::set_symmetric_difference;
using std::set_union;
using std::is_heap;
using std::is_heap_until;
using std::make_heap;
using std::push_heap;
using std::pop_heap;
using std::sort_heap;
using std::max;
using std::max_element;
using std::min;
using std::min_element;
using std::minmax;
using std::minmax_element;
using std::equal;
using std::lexicographical_compare;
using std::is_permutation;
using std::next_permutation;
using std::prev_permutation;
using std::iota;
using std::accumulate;
using std::inner_product;
using std::adjacent_difference;
using std::partial_sum;
using std::begin;
using std::end;
using std::plus;
using std::minus;
using std::multiplies;
using std::divides;
using std::modulus;
using std::negate;
using std::equal_to;
using std::not_equal_to;
using std::greater;
using std::less;
using std::greater_equal;
using std::less_equal;
using std::logical_and;
using std::logical_or;
using std::logical_not;
using std::bit_and;
using std::bit_or;
using std::bit_xor;
using std::hash;
using std::mt19937;
using std::mt19937_64;
using std::random_device;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
#define fup_s(i, a, b, s) for (long i = a, c = b; i <= c; i += s)
#define fwn_s(i, a, b, s) for (long i = b, c = a; c <= i; i -= s)
#define fup(i, a, b) fup_s(i, a, b, 1)
#define fwn(i, a, b) fwn_s(i, a, b, 1)
#define endl '\n'
#define tail(len) ((len) - 1)
#define offset(st, off) ((st) + (off))
#define mirror(len, i) offset(tail((len)), -(i))
#define range(st, len) (st), offset((st), tail((len)))
#define range_r(ed, len) offset((ed), -tail((len))), (ed)
#define range_mirror_point(len, a, b) mirror((len), (b)), mirror((len), (a))
#define range_mirror(len, st, off) range_mirror_point((len), (st), offset((st), tail((off))))
typedef unsigned long ul;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
const int inf32 = 1 << 30;
const ll inf64 = 1ll << 60;
const double pi = acos(-1);
const double eps = 1e-6;
template<typename tp>
int bitcount(tp x) {
	bool isll = sizeof(x) - 4;
	if (isll) {
		return __builtin_popcountll(x);
	} else {
		return __builtin_popcount(x);
	}
}
template<typename tp>
int clz(tp x) {
	bool isll = sizeof(x) - 4;
	if (isll) {
		return __builtin_clzll(x);
	} else {
		return __builtin_clz(x);
	}
}
template<typename tp>
int ctz(tp x) {
	bool isll = sizeof(x) - 4;
	if (isll) {
		return __builtin_ctzll(x);
	} else {
		return __builtin_ctz(x);
	}
}
template<typename tp>
int clo(tp x) {
	bool isll = sizeof(x) - 4;
	if (isll) {
		return x ? 1 << (64 - 1 - __builtin_clzll(x)) : 0;
	} else {
		return x ? 1 << (32 - 1 - __builtin_clz(x)) : 0;
	}
}
template<typename tp>
int cto(tp x) {
	bool isll = sizeof(x) - 4;
	if (isll) {
		return x ? 1 << __builtin_ctzll(x) : 0;
	} else {
		return x ? 1 << __builtin_ctz(x) : 0;
	}
}
ull roundup_pow_of_2(ull x) { return x ? clo(x) << 1 : 0; }
ull rounddown_pow_of_2(ull x) { return x ? clo(x) : 0; }
bool is_power_of_2(ull x) { return x && !(x & (x - 1)); }
ull length(ull l, ull r) { return (r < l) ? 0 : r - l + 1; }
bool inrange(ll x, ll l, ll r) { return r < l ? false : l <= x && x <= r; }
ull midpoint(ull l, ull r) { return l + ((r - l) >> 1); }
template<typename tp>
void range_normalize(tp &l, tp &r) { if (r < l) swap(l, r); }
/*
 * dir: find in left or right.
 * contain: can be equal or not.
 * whatever, key can be not found, thus return index will flow,
 * be careful to check return point, if must.
 * one way to check the return point is
 * check point in range and compare with key.
 * dir: 0, contain: 0. -> (. left flow.
 * dir: 0, contain: 1. -> [. right flow.
 * dir: 1, contain: 0. -> ). right flow.
 * dir: 1, contain: 1. -> ]. left flow.
 */
template<typename tp>
int binary_search(
		vector<tp> &v, int lo, int hi, tp key, bool dir, bool contain)
{
	range_normalize(lo, hi);
	while (lo <= hi) {
		int mid = midpoint(lo, hi), now = v[mid];
		if (!dir) {
			if (now < key)
				lo = mid + 1;
			else
				hi = mid - 1;
		} else {
			if (key < now)
				hi = mid - 1;
			else
				lo = mid + 1;
		}
	}
	return dir ^ contain ? lo : hi;
}
template<typename tp>
tp presum_point(vector<tp> &sum, int i) { return 0 <= i ? sum[i] : 0; }
template<typename tp>
tp presum_range(vector<tp> &sum, int l, int r)
{
	return sum[r] - presum_point(sum, l - 1);
}
template<typename tp>
void presum_preprocess(
						vector<tp> &sum, vector<tp> &data,
						int l, int r, int st)
{
	int len = length(l, r);
	sum.resize(sum.size() + len);
	for (long i = st, d = l; d <= r; ++i, ++d)
		sum[i] = presum_point(sum, i - 1) + data[d];
}
template<typename tp>
tp premul_point(vector<tp> &mul, int i) { return 0 <= i ? mul[i] : 1; }
template<typename tp>
tp premul_range(vector<tp> &mul, int l, int r)
{
	return mul[r] / premul_point(mul, l - 1);
}
template<typename tp>
void premul_preprocess(
						vector<tp> &mul, vector<tp> &data,
						int l, int r, int st)
{
	int len = length(l, r);
	mul.resize(mul.size() + len);
	for (long i = st, d = l; d <= r; ++i, ++d)
		mul[i] = premul_point(mul, i - 1) * data[d];
}
ll div_roundup(ll x, ll div) { return (x + div - 1) / div; }
ll div_rounddown(ll x, ll div) { return x / div; }
ll round_shift(ll x, ll dist, ll l, ll r)
{
	int len = length(l, r);
	return ((x - l + dist) % len + len) % len + l;
}
ll gcd(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
ull mul_mod(ull a, ull b, ull mod)
{
	ull res = (a * b - (ll)(a / (ldb)mod * b + 1e-3) * mod + mod) % mod;
	return res;
}
ll pow_mod(ll x, ll n, ll mod)
{
	ll res = 1;
	while (n > 0) {
		if (n & 1)
			res = mul_mod(res, x, mod);
		x = mul_mod(x, x, mod);
		n >>= 1;
	}
	return res;
}
ull random(ull mod)
{
	return (ull)(mod * (rand() / (double)RAND_MAX));
}
template<typename tp>
void combine(size_t &seed, const tp &x)
{
	seed ^= std::hash<tp>()(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
void hash_val(size_t &seed) {}
template<typename tp, typename ...other>
void hash_val(size_t &seed, tp &val, const other &...args)
{
	combine(seed, val);
	hash_val(seed, args...);
}
template<typename tp>
size_t hash_val(const std::vector<tp> &vec)
{
	size_t seed = 0;
	for (auto x : vec) {
		combine(seed, x);
	}
	return seed;
}
template<typename ...tp>
size_t hash_val(const tp &...args)
{
	size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}
int fdu(double x)
{
	return fabs(x) < eps ? 0 : x <= -eps ? -1 : 1;
}
// like ecvt, fcvt, gcvt...
double fcut(double x, int xp)
{
	return 1.L * (ll)(x * pow(10, xp)) / pow(10, xp);
}
template<typename tp>
void read(tp &x)
{
	cin >> x;
}
template<typename tp>
void read_vec(vector<tp> &v, size_t n)
{
	v.resize(n);
	fup(i, 0, v.size() - 1) {
		cin >> v[i];
	}
}

class data {
public:
	bool in() {
		return !cin.eof();
	}
	void deal() {
	}
	void out() {
	}
} gkd;

class task {
	int testcase = 1 << 30;
	stringstream tid;
	data &gao = gkd;
public:
	task(
		bool multicase = false,
		bool testid = false,
		bool blankline = false) {
		ios::sync_with_stdio(0);
		cin.tie(0);
		cout.setf(ios::fixed);
		cout.precision(20);
		if (multicase)
			read(testcase);
		for (int ti = 1; ti <= testcase && gao.in(); ++ti) {
			gao.deal();
			if (blankline && 1 < ti)
				cout << endl;
			tid << "Case #" << ti << ": ";
			if (testid)
				cout << tid.str();
			gao.out();
			tid.str("");
		}
	}
};

template<typename tp>
void counting_sort(vector<tp> &v, tp chunk, uint blk)
{
	auto bit = [=](tp x) {
		return x >> ctz(chunk) & (blk - 1);
	};
	vector<tp> cnt(blk, 0), cp(v.size());
	for (auto x : v)
		cnt[bit(x)]++;
	partial_sum(cnt.begin(), cnt.end(), cnt.begin());
	fwn (i, 0, v.size() - 1) {
		tp &x = v[i];
		cp[--cnt[bit(x)]] = x;
	}
	copy(cp.begin(), cp.end(), v.begin());
}
template<typename tp>
void radix_sort_slow(vector<tp> &v, uint blk = 1 << 8)
{
	if (std::is_signed<tp>::value) {
		typedef typename std::make_unsigned<tp>::type utp;
		auto is_minus = [](tp x) { return x < 0; };
		int sz = count_if(v.begin(), v.end(), is_minus);
		vector<utp> po(v.size() - sz), ne(sz);
		po.resize(remove_copy_if(v.begin(), v.end(), po.begin(), is_minus) - po.begin());
		ne.resize(copy_if(v.begin(), v.end(), ne.begin(), is_minus) - ne.begin());
		radix_sort_slow(ne, blk);
		radix_sort_slow(po, blk);
		copy(po.begin(), po.end(),
				copy(ne.begin(), ne.end(), v.begin()));
	} else {
		tp chunk = 1;
		while (1) {
			if (is_sorted(v.begin(), v.end()))
				break;
			counting_sort(v, chunk, blk);
			if (chunk << ctz(blk) < chunk)
				break;
			chunk <<= ctz(blk);
		}
	}
}
/*
 * notice: tp should be unsigned, only deal positive number.
 * assume that number value limit is 10 ^ 9 or 10 ^ 18, then the
 * 1 << 30 and 1ll << 60 will greater than them.
 * in this environment, we use 1 << 10 or 1 << 5 be the blk is faster, because
 * 5 and 10 is divide by 30 and 60. we can also use 1 << 8 be the blk.
 */
typedef uint32_t uint;
typedef uint64_t ulong;
template<typename tp>
void radix_sort_fast(vector<tp> &v, uint blk = 1 << 8)
{
	if (std::is_signed<tp>::value) {
		typedef typename std::make_unsigned<tp>::type utp;
		auto is_minus = [](tp x) { return x < 0; };
		int sz = count_if(v.begin(), v.end(), is_minus);
		vector<utp> po(v.size() - sz), ne(sz);
		po.resize(remove_copy_if(v.begin(), v.end(), po.begin(), is_minus) - po.begin());
		ne.resize(copy_if(v.begin(), v.end(), ne.begin(), is_minus) - ne.begin());
		radix_sort_fast(ne, blk);
		radix_sort_fast(po, blk);
		copy(po.begin(), po.end(),
		copy(ne.begin(), ne.end(), v.begin()));
	} else {
		vector<vector<tp>> radix(blk);
		vector<tp> all;
		tp chunk = 1;
		for (auto x : v)
			all.emplace_back(x);
		while (1) {
			if (is_sorted(all.begin(), all.end()))
				break;
			for (auto x : all)
				radix[x >> ctz(chunk) & (blk - 1)].emplace_back(x);
			all.clear();
			for (auto &cur : radix) {
				if (!cur.empty()) {
					for (auto x : cur) {
						all.emplace_back(x);
					}
					cur.clear();
				}
			}
			if (chunk << ctz(blk) < chunk)
				break;
			chunk <<= ctz(blk);
		}
		copy(all.begin(), all.end(), v.begin());
	}
}

template<typename tp, class twist = mt19937_64>
class random_int {
	using dist = uniform_int_distribution<tp>;
	using param_type = typename dist::param_type;
	dist segment;
	twist gen{random_device{}()};
public:
	void set(tp l, tp r) {
		segment.param(param_type{l, r});
	}
	pair<tp, tp> get() {
		assert(segment.a() == segment.min());
		assert(segment.b() == segment.max());
		return {segment.a(), segment.b()};
	}
	tp operator()() {
		return segment(gen);
	}
};
template<typename tp, class twist = mt19937_64>
class random_real {
	using dist = uniform_real_distribution<tp>;
	using param_type = typename dist::param_type;
	dist segment;
	twist gen{random_device{}()};
public:
	void set(tp l, tp r) {
		segment.param(param_type{l, r});
	}
	pair<tp, tp> get() {
		assert(segment.a() == segment.min());
		assert(segment.b() == segment.max());
		return {segment.a(), segment.b()};
	}
	tp operator()() {
		return segment(gen);
	}
};

template<typename tp>
void test_slow(int sz, int d)
{
	vector<tp> v(sz);
	double t1, t2;
	random_int<tp> rd;
	rd.set(tp(0), tp(~0));
	fup (i, 0, sz - 1)
		v[i] = rd();
	t1 = clock();
	radix_sort_slow(v, 1 << d);
	t2 = clock();
	cout << (t2 - t1) / 1000 << ' ' << is_sorted(v.begin(), v.end()) << endl;
}
template<typename tp>
void test_fast(int sz, int d)
{
	vector<tp> v(sz);
	double t1, t2;
	random_int<tp> rd;
	rd.set(tp(0), tp(~0));
	fup (i, 0, sz - 1)
		v[i] = rd();
	t1 = clock();
	radix_sort_fast(v, 1 << d);
	t2 = clock();
	cout << (t2 - t1) / 1000 << ' ' << is_sorted(v.begin(), v.end()) << endl;
}
void test()
{
	srand(time(0));
	const int sz = 5000000;
	for (auto d : {4, 5, 6, 8, 10}) {
		cout << "\ntest: " << d <<endl;
		test_slow<int>(sz, d);
		test_slow<uint>(sz, d);
		test_slow<ll>(sz, d);
		test_slow<ull>(sz, d);
	}
}

__attribute__((optimize("-Ofast"))) int main()
{
	test();
	return 0;
}
