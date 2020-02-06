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
#include <functional>
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
#include <ext/pb_ds/assoc_container.hpp>
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
using std::function;
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
using namespace __gnu_pbds;
template<typename key>
using ordered_set = __gnu_pbds::tree<
						key, __gnu_pbds::null_type, less<key>, __gnu_pbds::rb_tree_tag,
						__gnu_pbds::tree_order_statistics_node_update>;
template<typename key, typename val>
using ordered_map = __gnu_pbds::tree<
						key, val, less<key>, __gnu_pbds::rb_tree_tag,
						__gnu_pbds::tree_order_statistics_node_update>;
#define DEBUG(...) cout << __LINE__ << ": "; debug_line(__VA_ARGS__)
#define fup_s(i, a, b, s) for (long i = a, c = b; i <= c; i += s)
#define fwn_s(i, a, b, s) for (long i = b, c = a; c <= i; i -= s)
#define fup(i, a, b) fup_s(i, a, b, 1)
#define fwn(i, a, b) fwn_s(i, a, b, 1)
#define it_each(obj) (obj).begin(), (obj).end()
#define it_i(obj, i) (obj).begin() + (i)
#define it_range(obj, l, r) it_i(obj, l), it_i(obj, r)
#define it_prefix(obj, i) (obj).begin(), it_i(obj, i)
#define it_suffix(obj, i) it_i(obj, i), (obj).end()
#define endl '\n'
#define tail(len) ((len) - 1)
#define offset(st, off) ((st) + (off))
#define mirror(len, i) offset(tail((len)), -(i))
#define range(st, len) (st), offset((st), tail((len)))
#define range_r(ed, len) offset((ed), -tail((len))), (ed)
#define range_mirror_point(len, a, b) mirror((len), (b)), mirror((len), (a))
#define range_mirror(len, st, off) range_mirror_point((len), (st), offset((st), tail((off))))
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
const int inf32 = 1 << 30;
const ll inf64 = 1ll << 60;
const double pi = acos(-1);
const double eps = 1e-6;
template<typename tp>
void print(const tp &x) { cout << x << ' '; }
template<typename ...tp>
void debug_line(tp &&...args)
{
	initializer_list<int>{(print(forward<tp>(args)), 0)...};
	cout << endl;
}
/*
 * calc expression for basic arithmetic.
 * not judge illegal situation.
 * not use stringstream(it may be slow).
 * skip space use `isblank`, not `isspace`, so just read one-line.
 * if read multi-line expression... use `isspace`, good luck.
 * originally, i envisage use that to do complex mod calculation, but now
 * not implement. if to implement, write like a class.
 */
template<typename tp>
tp parse_calc_exp(const string &exp)
{
	stack<char> cop;
	stack<tp> nop;
	int cur = 0, len = exp.length(), minus = 1;
	char ch;
	bool flag = 0;
	auto push_num = [&](stack<tp> &nop, tp x) {
		nop.push(x);
		flag = 1;
	};
	auto calc = [&](stack<char> &cop, stack<tp> &nop) {
		tp ret, e1, e2;
		char op;
		bool ok = 1 <= cop.size() && 2 <= nop.size();
		if (!ok)
			return;
		op = cop.top(); cop.pop();
		e2 = nop.top(); nop.pop();
		e1 = nop.top(); nop.pop();
		switch (op) {
			case '+':
				ret = e1 + e2;
				break;
			case '-':
				ret = e1 - e2;
				break;
			case '*':
				ret = e1 * e2;
				break;
			case '/':
				ret = e1 / e2;
				break;
			case '%':
				ret = e1 % e2;
				break;
			case '^':
				ret = pow(e1, e2);
				break;
			default:
				ok = 0;
				break;
		}
		if (ok)
			push_num(nop, ret);
	};
	auto can_push = [](char lef, char rig) {
		bool ok;
		string plus("+-"), multiply("*/%^");
		ok = rig != ')' && (lef == '(' || rig == '('
			|| (plus.find(lef) != -1ull && multiply.find(rig) != -1ull));
		return ok;
	};
	while (cur < len) {
		while (isblank(ch = exp[cur]))
			cur++;
		if (isdigit(ch)) {
			size_t ed = exp.find_first_not_of("0123456789", cur);
			if (ed == -1ull)
				ed = len;
			if (sizeof(tp) - 4)
				push_num(nop, stoll(exp.substr(cur, offset(ed, -cur))) * minus);
			else
				push_num(nop, stoi(exp.substr(cur, offset(ed, -cur))) * minus);
			minus = 1;
			cur = ed;
		} else {
			if (ch == '-' && !flag) {
				flag = 0;
				minus *= -1;
				goto end;
			}
			if (ch == ')') {
				while (!cop.empty() && cop.top() != '(')
					calc(cop, nop);
				if (cop.empty())
					goto end;
				cop.pop();
			} else {
				if (ch != '(')
					while (!cop.empty() && !can_push(cop.top(), ch))
						calc(cop, nop);
				cop.push(ch);
			}
end:
			cur++;
		}
	}
	while (!cop.empty()) {
		if (cop.top() == '(')
			cop.pop();
		else
			calc(cop, nop);
	}
	assert(nop.size() == 1);
	return nop.top();
}
template<typename tp>
tp va_exp(const char *fmt, ...)
{
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	vprintf(fmt, args);
	va_end(args);
	return parse_calc_exp<tp>(buf);
}
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
template<typename tp>
tp roundup_pow_of_2(tp x) { return x ? clo(x) << 1 : 0; }
template<typename tp>
tp rounddown_pow_of_2(tp x) { return x ? clo(x) : 0; }
template<typename tp>
bool is_power_of_2(tp x) { return x && !(x & (x - 1)); }
template<typename tp>
tp ltor(tp l, tp len) { return l + len - 1; }
template<typename tp>
tp rtol(tp r, tp len) { return r - len + 1; }
template<typename tp>
tp length(tp l, tp r) { return (r < l) ? 0 : r - l + 1; }
template<typename tp>
bool inrange(tp x, tp l, tp r) { return r < l ? false : l <= x && x <= r; }
template<typename tp>
tp midpoint(tp l, tp r) { return l + ((r - l) >> 1); }
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
template<typename tp>
tp div_roundup(tp x, tp div) { return (x + div - 1) / div; }
template<typename tp>
tp div_rounddown(tp x, tp div) { return x / div; }
template<typename tp>
tp round_shift(tp x, tp dist, tp l, tp r)
{
	int len = length(l, r);
	return ((x - l + dist) % len + len) % len + l;
}
template<typename tp>
tp gcd(tp a, tp b) { while (b) { a %= b; swap(a, b); } return a; }
template<typename tp>
tp lcm(tp a, tp b) { return a / gcd(a, b) * b; }
ull mul_mod(ull a, ull b, ull mod)
{
	ull res = (a * b - (ll)(a / (ldb)mod * b + 1e-3) * mod + mod) % mod;
	return res;
}
template<typename tp>
tp pow_mod(tp x, tp n, tp mod)
{
	if (mod == 1)
		return 0;
	tp res = 1;
	while (n > 0) {
		if (n & 1)
			res = mul_mod(res, x, mod);
		x = mul_mod(x, x, mod);
		n >>= 1;
	}
	return res;
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
void combine(size_t &seed, const tp &x)
{
	seed ^= hash<tp>()(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
void hash_val(size_t &seed) {}
template<typename tp, typename ...other>
void hash_val(size_t &seed, tp &val, const other &...args)
{
	combine(seed, val);
	hash_val(seed, args...);
}
template<typename tp>
size_t hash_val(const vector<tp> &vec)
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
ull bkdr_hash_range(const vector<ull> &hash, const vector<ull> &exp, int l, int r)
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

class sais
{
	string origin;
	vector<int> val, sa, rk, lcp;
public:
	void init(const string &str) {
		origin.assign(str);
		origin += '#';
		int sz = origin.size();
		val.resize(sz);
		sa.resize(sz);
		rk.resize(sz);
		lcp.resize(sz);
		val.assign(it_each(origin));
		get_sa(val, sa);
		get_lcp();
		fup (i, 1, sa.size() -  1)
			cout << sa[i] << " \n"[i == sa.size() - 1];
		fup (i, 1, lcp.size() - 1)
			cout << lcp[i] << " \n"[i == lcp.size() - 1];
	}
	void get_sa(vector<int> &text, vector<int> &sa) {
		int len = text.size();
		vector<int> bk, lbk, sbk, lms;
		vector<bool> type(len);
		auto is_lms_char = [&](int i) {
			return !type[i] && 0 < i && type[i - 1];
		};
		auto is_lms_equal = [&](int p1, int p2) {
			/*
			 * this judge can't deal one is lms and other is not lms,
			 * but text is equal, is think this can not judge equal.
			 * it is seems not affect sa.
			 */
			for (bool f1, f2; text[p1] == text[p2]
				&& (f1 = is_lms_char(++p1), f2 = is_lms_char(++p2), !(f1 & f2)););
			return (text[p1] == text[p2]);
		};
		auto reset_bk = [&]() {
			lbk[0] = sbk[0] = 0;
			fup (x, 1, bk.size() - 1) {
				lbk[x] = bk[x - 1];
				sbk[x] = bk[x] - 1;
			}
		};
		auto push_lbk = [&](int pos) {
			sa[lbk[text[pos]]++] = pos;
		};
		auto push_sbk = [&](int pos) {
			sa[sbk[text[pos]]--] = pos;
		};
		auto induced_sort = [&]() {
			fill(it_each(sa), -1);
			reset_bk();
			fwn (i, 0, lms.size() - 1)
				push_sbk(lms[i]);
			fup (i, 0, sa.size() - 1) if (0 < sa[i] && type[sa[i] - 1])
				push_lbk(sa[i] - 1);
			reset_bk();
			fwn (i, 0, sa.size() - 1) if (0 < sa[i] && !type[sa[i] - 1])
				push_sbk(sa[i] - 1);
		};
		int vmx = *max_element(it_each(text));
		bk.resize(vmx + 1);
		lbk.resize(vmx + 1);
		sbk.resize(vmx + 1);
		fill(it_each(bk), 0);
		for (auto x : text)
			bk[x]++;
		partial_sum(it_each(bk), bk.begin());
		type.back() = 0;
		fwn (i, 0, len - 2) {
			if (text[i] == text[i + 1])
				type[i] = type[i + 1];
			else
				type[i] = text[i] > text[i + 1];
		}
		fup (i, 1, len - 1)
			if (is_lms_char(i))
				lms.emplace_back(i);
		induced_sort();
		vector<int> rr(len);
		int cc = 0, last = -1;
		fill(it_each(rr), -1);
		fup (i, 0, len - 1) {
			int pos = sa[i];
			if (is_lms_char(pos)) {
				if (~last && !is_lms_equal(pos, last))
					cc++;
				rr[pos] = cc;
				last = pos;
			}
		}
		bool flag = cc + 1 == lms.size();
		vector<int> text1(lms.size()), sa1(lms.size());
		copy_if(it_each(rr), text1.begin(), [](int x) { return x != -1; });
		if (flag) {
			fup (i, 0, lms.size() - 1)
				sa1[text1[i]] = i;
		} else {
			get_sa(text1, sa1);
		}
		transform(it_each(sa1), sa1.begin(), [&](int x) { return lms[x]; });
		lms.swap(sa1);
		induced_sort();
	}
	void get_lcp() {
		fup (i, 0, sa.size() - 1)
			rk[sa[i]] = i;
		int d = 0;
		lcp[0] = 0;
		fup (p1, 0, sa.size() - 2) {
			if (d)
				d--;
			int p2 = sa[rk[p1] - 1];
			while (val[p1 + d] == val[p2 + d])
				d++;
			lcp[rk[p1]] = d;
		}
	}
};

class data {
	string s;
	sais sa;
	istream &ioend() {
		cin.setstate(ios_base::badbit);
		return cin;
	}
public:
	istream &in() {
		cin >> s;
		return cin;
	}
	void deal() {
		sa.init(s);
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
	//sais("GATAGACA"); // 8 7 5 3 1 6 4 0 2.
	//sais("abracadabra"); // 11 10 7 0 3 5 8 1 4 6 9 2.
	//sais("AGATGAGATACGCGGT"); // 16 9 5 0 7 2 10 12 4 6 1 11 13 14 15 8 3.
	//sais("mmiissiissiippii"); // 16 15 14 10 6 2 11 7 3 1 0 13 12 9 5 8 4.
	//sais("zefefefefefefefefefefefefefefefefefefef"); // test is_lms_equal.
	task gao{};
	return 0;
}
