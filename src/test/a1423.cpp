/*
 * 魔方题, 仅测模板用.
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse4")
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <random>
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
using std::tuple;
using std::tie;
using std::get;
using std::pair;
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
using std::bit_not;
#define fup_s(i, a, b, s) for (long i = a, c = b; i <= c; i += s)
#define fwn_s(i, a, b, s) for (long i = b, c = a; c <= i; i -= s)
#define fup(i, a, b) fup_s(i, a, b, 1)
#define fwn(i, a, b) fwn_s(i, a, b, 1)
#define it_each(obj) (obj).begin(), (obj).end()
#define it_i(obj, i) (obj).begin() + (i)
#define it_range(obj, l, r) it_i(obj, l), it_i(obj, r)
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
		const vector<tp> &v, int lo, int hi, tp key, bool dir, bool contain)
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
tp presum_point(const vector<tp> &sum, int i) { return 0 <= i ? sum[i] : 0; }
template<typename tp>
tp presum_range(const vector<tp> &sum, int l, int r)
{
	return sum[r] - presum_point(sum, l - 1);
}
template<typename tp>
void presum_preprocess(
						vector<tp> &sum, const vector<tp> &data,
						int l, int r, int st)
{
	int len = length(l, r);
	sum.resize(sum.size() + len);
	for (long i = st, d = l; d <= r; ++i, ++d)
		sum[i] = presum_point(sum, i - 1) + data[d];
}
template<typename tp>
tp premul_point(const vector<tp> &mul, int i) { return 0 <= i ? mul[i] : 1; }
template<typename tp>
tp premul_range(const vector<tp> &mul, int l, int r)
{
	return mul[r] / premul_point(mul, l - 1);
}
template<typename tp>
void premul_preprocess(
						vector<tp> &mul, const vector<tp> &data,
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
template<typename tp, class twist = std::mt19937_64>
class random_int {
	std::uniform_int_distribution<tp> fuck;
	using param_type = decltype(fuck.param());
	twist shit{std::random_device{}()};
public:
	void set_range(tp l, tp r) {
		fuck.param(param_type {l, r});
	}
	pair<tp, tp> get_range() {
		assert(fuck.a() == fuck.min());
		assert(fuck.b() == fuck.max());
		return {fuck.a(), fuck.b()};
	}
	tp operator()() {
		return fuck(shit);
	}
};
template<typename tp, class twist = std::mt19937_64>
class random_real {
	std::uniform_real_distribution<tp> fuck;
	using param_type = decltype(fuck.param());
	twist shit{std::random_device{}()};
public:
	void set_range(tp l, tp r) {
		fuck.param(param_type {l, r});
	}
	pair<tp, tp> get_range() {
		assert(fuck.a() == fuck.min());
		assert(fuck.b() == fuck.max());
		return {fuck.a(), fuck.b()};
	}
	tp operator()() {
		return fuck(shit);
	}
};
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
void bkdr_hash_preprocess(const string &seq, vector<ull> &hash, ull seed, int i = 0)
{
	if (hash.size() < i + seq.size())
		hash.resize(i + seq.size());
	for (auto h : seq) {
		hash[i] = presum_point(hash, i - 1) * seed + h;
	}
}
template<typename tp>
void bkdr_hash_preprocess(const vector<tp> &seq, vector<ull> &hash, ull seed, int i = 0)
{
	if (hash.size() < i + seq.size())
		hash.resize(i + seq.size());
	for (auto h : seq) {
		hash[i] = presum_point(hash, i - 1) * seed + h;
	}
}
ull bkdr_hash_once(const string &seq, ull seed)
{
	ull hash = 0;
	for (auto h : seq)
		hash = hash * seed + h;
	return hash;
}
template<typename tp>
ull bkdr_hash_once(const vector<tp> &seq, ull seed)
{
	ull hash = 0;
	for (auto h : seq)
		hash = hash * seed + h;
	return hash;
}
ull hash_range(const vector<ull> &hash, const vector<ull> &exp, int l, int r)
{
	return hash[r] - presum_point(hash, l - 1) * exp[length(l, r)];
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

template<size_t dn>
class permutation
{
	static int origin[dn];
	void gall() { ghs(); ginv(); gcyc(); }
	void ghs() {
		for (int i = 0; i < 2; ++i)
			hs[i] = hash_val(vector<int>(mat[i], mat[i] + dn));
	}
	void ginv() {
		auto fn = [=, i = 0](int x) mutable { mat[1][x] = i++; };
		for_each(mat[0], mat[0] + dn, fn);
	}
	void gcyc() {
		bool vis[dn];
		cycn = 0;
		period = 1;
		memset(vis, 0, sizeof vis);
		fup (x, 0, dn - 1) {
			cycle[0][x].clear();
			cycle[1][x].clear();
			if (!vis[x]) {
				int nx = x;
				while (!vis[nx]) {
					vis[nx] = 1;
					cycle[0][cycn].push_back(nx);
					cycle[1][cycn].push_back(nx);
					nx = mat[0][nx];
				};
				reverse(cycle[1][cycn].begin(), cycle[1][cycn].end());
				period = lcm(period, cycle[0][cycn].size());
				cycn++;
			}
		}
	}
public:
	static void init() {
		iota(origin, origin + dn, 0);
	}
	int mat[2][dn];
	ull hs[2];
	vector<int> cycle[2][dn];
	int cycn, period;
	permutation() {
		iota(mat[0], mat[0] + dn, 0);
		gall();
	}
	permutation(const vector<int> &p) { assign(p); }
	permutation(const vector<int> &pre, const vector<int> &nxt) { assign(pre, nxt); }
	void assign(const vector<int> &p) {
		assert(is_permutation(origin, origin + dn, p.begin()));
		copy(p.begin(), p.end(), mat[0]);
		gall();
	}
	void assign(const vector<int> &pre, const vector<int> &nxt) {
		auto fn = [](int x) { return inrange(x, 0, dn - 1); };
		assert(find_if_not(pre.begin(), pre.end(), fn) == pre.end());
		assert(find_if_not(nxt.begin(), nxt.end(), fn) == nxt.end());
		assert(is_permutation(pre.begin(), pre.end(), nxt.begin()));
		permutation();
		for (int i = 0; i < pre.size(); ++i) {
			mat[0][pre[i]] = nxt[i];
		}
		gall();
	}
	void compos(permutation<dn> &rhs, int tp) {
		auto fn = [=](int x) { return rhs.mat[tp][x]; };
		transform(mat[0], mat[0] + dn, mat[0], fn);
		gall();
	}
};
template<size_t dn>
int permutation<dn>::origin[];
template<size_t dn>
using pm = permutation<dn>;
template<size_t dn>
using vpm = vector<permutation<dn>>;

template<size_t dn>
class cube
{
	static pm<dn> origin;
public:
	static void init() {
		permutation<dn>::init();
		origin = pm<dn>();
	}
	static void level_bfs(vpm<dn> &misc, int limit, vpm<dn> &comb) {
		queue<pm<dn>> que[2];
		set<ull> st;
		int qid = 0;
		que[qid].push(origin);
		st.insert(origin.hs[0]);
		comb.push_back(origin);
		for (int lev = 0; lev < limit; ++lev) {
			if (que[qid].empty())
				break;
			while (!que[qid].empty()) {
				pm<dn> x = que[qid].front(); que[qid].pop();
				for (auto y : misc) {
					x.compos(y, 0);
					if (!st.count(x.hs[0])) {
						que[qid ^ 1].push(x);
						st.insert(x.hs[0]);
						comb.push_back(x);
					}
					x.compos(y, 1);
				}
			}
			qid ^= 1;
		}
	}
	static void face_seq(vpm<dn> &body, vpm<dn> &face, vpm<dn> &comb) {
		pm<dn> once = origin;
		set<ull> st;
		st.insert(once.hs[0]);
		comb.push_back(once);
		for (auto x : body) {
			for (auto y : face) {
				once.compos(x, 0);
				once.compos(y, 0);
				once.compos(x, 1);
				if (!st.count(x.hs[0])) {
					st.insert(x.hs[0]);
					comb.push_back(once);
				}
				once.compos(y, 1);
			}
		}
	}
};
template<size_t dn>
pm<dn> cube<dn>::origin;

class data {
	ll n, p, mod, ans;
	vpm<30> face, buf;
	int mmp[35];
public:
	bool in() {
		cin >> n >> p;
		return !cin.eof();
	}
	void preprocess() {
		cube<30>::init();
		face.resize(3);
		face[0].assign(
			{9,10,11,12,13,14,15,16,17,0,1,2,3,4,5,6,7,8,20,19,18,29,28,27,26,25,24,23,22,21});
		face[1].assign(
			{2,5,8,1,4,7,0,3,6,15,12,9,16,13,10,17,14,11,21,22,23,24,25,26,27,28,29,18,19,20});
		face[2].assign(
			{9,10,11,3,4,5,6,7,8,0,1,2,12,13,14,15,16,17,20,19,18,29,22,23,24,25,26,27,28,21});
		cube<30>::level_bfs(face, 100233, buf);
		memset(mmp, 0, sizeof mmp);
		fup (ci, 0, buf.size() - 1) {
			auto xp = buf[ci];
			mmp[xp.cycn]++;
		}
	}
	void deal() {
		ans = 0;
		mod = p * buf.size();
		for (int x = 1; x <= 30; ++x) {
			ans = (ans + mmp[x] * pow_mod(n, x, mod) % mod) % mod;
		}
		ans /= buf.size();
	}
	void out() {
		cout << ans << '\n';
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
			cin >> testcase;
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
	gkd.preprocess();
	task gao(1, 0, 0);
	return 0;
}
