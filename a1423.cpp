/**
 * 通用头文件.
 *
 * todolist:
 * 一些数学函数, 几何相关?
 * 二维, 三维数组的遍历方向数组. 二维的4向, 8向; 三维的6向, 26向(可能不需要)...
 * 快速读入, istream.rdbuf->sgetn(buf, sizeof(buf)), 配合readint...
 * 开栈.
 * debug辅助.
 * builtin位操作, 有ll版本, 加上.
 * efg_cvt, 浮点数截断.
 * 前缀和, 前缀积, 可加dist,dir. 写成template.
 * mt19937...
 * 模运算类.
 * http://codeforces.com/contest/1261/submission/65651526
 */
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
#define range(st, len) (st), (st) + tail(len)
#define range_r(ed, len) (ed) - tail(len), (ed)
typedef unsigned long ul;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
const int inf32 = 1 << 30;
const ll inf64 = 1ll << 60;
const double pi = acos(-1);
const double eps = 1e-6;
ul bitcount(ul x) {return __builtin_popcount(x);}
ul clz(ul x) {return __builtin_clz(x);}
ul ctz(ul x) {return __builtin_ctz(x);}
ul clo(ul x) {return x ? 1 << (32 - 1 - clz(x)) : 0;}
ul cto(ul x) {return x ? 1 << ctz(x) : 0;}
ull bitcountll(ull x) {return __builtin_popcountll(x);}
ull clzll(ull x) {return __builtin_clzll(x);}
ull ctzll(ull x) {return __builtin_ctzll(x);}
ull cloll(ull x) {return x ? 1 << (64 - 1 - clz(x)) : 0;}
ull ctoll(ull x) {return x ? 1 << ctz(x) : 0;}
ul roundup_pow_of_2(ul x) {return x ? clo(x) << 1 : 0;}
ul rounddown_pow_of_2(ul x) {return x ? clo(x) : 0;}
bool is_power_of_2(ull x) {return x && !(x & (x - 1));}
void range_normalize(ll &l, ll &r) {if (r < l) swap(l, r);}
ull length(ull l, ull r) {return r - l + 1;}
bool inrange(ll x, ll l, ll r) {return r < l ? false : l <= x && x <= r;}
ull midpoint(ull l, ull r) {return l + ((r - l) >> 1);}
ll presum_point(vector<ll> &sum, int i) {return i ? sum[i] : 0;}
ll presum_range(vector<ll> &sum, int l, int r)
{return sum[r] - presum_point(sum, l - 1);}
void presum_preprocess(
						vector<ll> &sum, vector<ll> &data,
						int l, int r, int st)
{
	int len = length(l, r);
	sum.resize(sum.size() + len);
	for (long i = st, d = l; d <= r; ++i, ++d) {
		sum[i] = presum_point(sum, i - 1) + data[d];
	}
}
ll premul_point(vector<ll> &mul, int i) {return i ? mul[i] : 1;}
ll premul_range(vector<ll> &mul, int l, int r)
{return mul[r] / premul_point(mul, l - 1);}
void premul_preprocess(
						vector<ll> &mul, vector<ll> &data,
						int l, int r, int st)
{
	int len = length(l, r);
	mul.resize(mul.size() + len);
	for (long i = st, d = l; d <= r; ++i, ++d) {
		mul[i] = premul_point(mul, i - 1) * data[d];
	}
}
ll div_roundup(ll x, ll div) {return (x + div - 1) / div;}
ll div_rounddown(ll x, ll div) {return x / div;}
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
		if (n & 1) res = mul_mod(res, x, mod);
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
};
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

template<size_t dn>
class permutation
{
	static int origin[dn + 1];
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
		bool vis[dn + 1];
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
		auto fn = [=, i = 0](void) mutable { return i++; };
		generate(origin, origin + dn, fn);
	}
	int mat[2][dn + 1];
	ull hs[2];
	vector<int> cycle[2][dn + 1];
	int cycn, period;
	permutation() {
		auto fn = [=, i = 0](void) mutable { return i++; };
		generate(mat[0], mat[0] + dn, fn);
		gall();
	}
	permutation(vector<int> &&p) { assign(p); }
	permutation(vector<int> &&pre, vector<int> &&nxt) { assign(pre, nxt); }
	void assign(vector<int> &&p) {
		assert(is_permutation(origin, origin + dn, p.begin()));
		copy(p.begin(), p.end(), mat[0]);
		gall();
	}
	void assign(vector<int> &&pre, vector<int> &&nxt) {
		auto fn = [](int x) { return 0 <= x && x <= dn - 1; };
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
