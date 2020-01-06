#pragma GCC optimize("Ofast")
#pragma GCC target("sse4")
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <bitset>
#include <tr2/dynamic_bitset>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename tp>
using ordered_set = tree<
						tp, null_type, std::less<tp>, rb_tree_tag,
						tree_order_statistics_node_update>;
template<typename key, typename val>
using ordered_map = tree<
						key, val, std::less<key>, rb_tree_tag,
						tree_order_statistics_node_update>;
using std::ios;
using std::istream;
using std::ostream;
using std::stringstream;
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::deque;
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
using std::for_each;
using std::swap;
using std::generate;
using std::transform;
using std::accumulate;
using std::adjacent_difference;
using std::partial_sum;
using std::is_permutation;
using std::prev_permutation;
using std::next_permutation;
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

__attribute__((optimize("-Ofast"))) int main()
{
	task gao(0, 0, 0);
	return 0;
}
