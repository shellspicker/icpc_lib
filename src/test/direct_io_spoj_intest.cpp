#ifndef TEMPLATE_H
#define TEMPLATE_H

#pragma GCC optimize(1,2,3,"Ofast","inline")
#include <cstddef>
#include <cstdint>
#include <climits>
#include <ctime>
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
#ifdef linux
#include <ext/pb_ds/assoc_container.hpp>
#endif
using std::ios;
using std::ios_base;
using std::istream;
using std::ostream;
using std::stringstream;
using std::streambuf;
using std::cin;
using std::cout;
using std::string;
using std::move;
using std::forward;
using std::tuple;
using std::tie;
using std::get;
using std::pair;
using std::make_pair;
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
#ifdef linux
template<typename key>
using ordered_set = __gnu_pbds::tree<
						key, __gnu_pbds::null_type, less<key>, __gnu_pbds::rb_tree_tag,
						__gnu_pbds::tree_order_statistics_node_update>;
template<typename key, typename val>
using ordered_map = __gnu_pbds::tree<
						key, val, less<key>, __gnu_pbds::rb_tree_tag,
						__gnu_pbds::tree_order_statistics_node_update>;
#endif
#define endl '\n'
#define fup_s(i, a, b, s) for (int i = a, foc = b; i <= foc; i += s)
#define fwn_s(i, a, b, s) for (int i = b, foc = a; foc <= i; i -= s)
#define fup(i, a, b) fup_s(i, a, b, 1)
#define fwn(i, a, b) fwn_s(i, a, b, 1)
#define it_each(obj) (obj).begin(), (obj).end()
#define it_i(obj, i) (obj).begin() + (i)
#define it_i_rev(obj, i) (obj).end() - 1 - (i)
#define it_seg(obj, l, r) it_i(obj, l), it_i(obj, r)
#define it_seg_rev(obj, l, r) it_i_rev(obj, r), it_i_rev(obj, l)
#define it_range(obj, st, off) it_seg(obj, st, (st) + (off) - 1)
#define it_range_r(obj, ed, off) it_seg(obj, st, (ed) - (off) + 1)
#define it_range_rev(obj, st, off) it_seg_rev(obj, it_range(obj, st, off))
#define it_range_r_rev(obj, ed, off) it_seg_rev(obj, it_range_r(obj, ed, off))
#define it_prefix(obj, i) (obj).begin(), it_i(obj, i)
#define it_suffix(obj, i) it_i(obj, i), (obj).end()
#define i_rev(len, i) (len) - 1 - (i)
#define seg_rev(len, a, b) i_rev((len), (b)), i_rev((len), (a))
#define range(st, off) (st), (st) + (off) - 1
#define range_r(ed, off) (ed) - (off) + 1, (ed)
#define range_rev(len, st, off) seg_rev((len), range(st, off))
#define range_r_rev(len, ed, off) seg_rev((len), range_r(st, off))
#define finput(is, cls, obj) friend istream &operator >>(istream &is, cls &obj)
#define foutput(os, cls, obj) friend ostream &operator <<(ostream &os, const cls &obj)
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
const int inf32 = 1 << 30;
const ll inf64 = 1ll << 60;
const double pi = acos(-1);
const double eps = 1e-6;
template<typename tp>
int bitcount(tp x)
{
	if (4 < sizeof(x))
		return __builtin_popcountll(x);
	else
		return __builtin_popcount(x);
}
template<typename tp>
tp clz(tp x)
{
	if (4 < sizeof(x))
		return __builtin_clzll(x);
	else
		return __builtin_clz(x);
}
template<typename tp>
tp ctz(tp x)
{
	if (4 < sizeof(x))
		return __builtin_ctzll(x);
	else
		return __builtin_ctz(x);
}
template<typename tp>
tp clo(tp x)
{
	if (4 < sizeof(x))
		return x ? 1ll << (64 - 1 - __builtin_clzll(x)) : 0;
	else
		return x ? 1 << (32 - 1 - __builtin_clz(x)) : 0;
}
template<typename tp>
tp cto(tp x)
{
	if (4 < sizeof(x))
		return x ? 1ll << __builtin_ctzll(x) : 0;
	else
		return x ? 1 << __builtin_ctz(x) : 0;
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
bool inrange(tp x, tp l, tp r) { return r < l ? 0 : l <= x && x <= r; }
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
tp special(const vector<tp> &v, int i, tp val)
{
	if (inrange(i, 0, int(v.size() - 1)))
		return v[i];
	return val;
}
template<typename tp>
tp presum_range(const vector<tp> &sum, int l, int r)
{
	return sum[r] - special(sum, l - 1, 0);
}
template<typename tp>
void presum_preprocess(
						vector<tp> &&sum, const vector<tp> &data,
						int l, int r, int st)
{
	int len = length(l, r);
	sum.resize(sum.size() + len);
	for (int i = st, d = l; d <= r; ++i, ++d)
		sum[i] = special(sum, i - 1, 0) + data[d];
}
template<typename tp>
tp premul_range(const vector<tp> &mul, int l, int r)
{
	return mul[r] / special(mul, l - 1, 1);
}
template<typename tp>
void premul_preprocess(
						vector<tp> &&mul, const vector<tp> &data,
						int l, int r, int st)
{
	int len = length(l, r);
	mul.resize(mul.size() + len);
	for (int i = st, d = l; d <= r; ++i, ++d)
		mul[i] = special(mul, i - 1, 1) * data[d];
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
bool read(tp &x)
{
	return bool(cin >> x);
}
template<typename tp>
void read_vec(vector<tp> &v, size_t n)
{
	v.resize(n);
	fup(i, 0, v.size() - 1)
		cin >> v[i];
}
/*
 * 加速io, 基本类型都支持.
 */
class direct_io {
	static const int bsz = 1 << 10;
	char ibuf[bsz], obuf[bsz], *ihead = 0, *itail = 0, *ohead = obuf;
	streambuf *isb = cin.rdbuf(), *osb = cout.rdbuf();
	int output_float_digit = 15;
	char getchar() {
		if (ihead == itail)
			itail = (ihead = ibuf) + isb->sgetn(ibuf, bsz);
		return (ihead == itail) ? -1 : *ihead++;
	}
	void putchar(char ch) {
		if (ohead - obuf == bsz)
			osb->sputn(ohead = obuf, bsz);
		*ohead++ = ch;
	}
public:
	~direct_io() { osb->sputn(obuf, ohead - obuf); }
	void set_output_float_digit(int d) {
		output_float_digit = d;
	}
	bool input(char &ch) {
		if ((ch = getchar()) == -1)
			return 0;
		for (; ch ^ -1 && !isgraph(ch); ch = getchar());
		return ch ^ -1;
	}
	bool input(char *s) {
		char ch;
		if (!input(ch))
			return 0;
		for (*s++ = ch; ch = getchar(), ch ^ -1 && isgraph(ch); *s++ = ch);
		*s++ = 0;
		return 1;
	}
	bool input(string &s) {
		s.clear();
		char ch;
		if (!input(ch))
			return 0;
		for (s += ch; ch = getchar(), ch ^ -1 && isgraph(ch); s += ch);
		return 1;
	}
	// 适用于正负数, (int, long long, double).
	template<typename tp>
	bool input(tp &ret) {
		char ch;
		int sgn;
		tp bit = 0.1;
		if (ch = getchar(), ch == -1)
			return 0;
		for (; ch != -1 && ch != '-' && ch != '.' && !isdigit(ch); ch = getchar());
		sgn = (ch == '-') ? -1 : 1;
		ret = isdigit(ch) ? (ch ^ 48) : 0;
		if (ch == '.')
			goto read_float;
		for (; ch = getchar(), ch ^ -1 && isdigit(ch);)
			ret = ret * 10 + (ch ^ 48);
		if (ch == -1 || !isgraph(ch))
			return ret *= sgn, ch ^ -1;
read_float:
		for (; ch = getchar(), ch ^ -1 && isdigit(ch);)
			ret += (ch ^ 48) * bit, bit /= 10;
		return ret *= sgn, ch ^ -1;
	}
	template<typename ...var>
	void input(var &&...args) {
		initializer_list<int>{(input(forward<var>(args)), 0)...};
	}
	void output(char ch) {
		putchar(ch);
	}
	void output(char *s) {
		for (; *s; s++)
			putchar(*s);
	}
	void output(string &s) {
		for (auto ch : s)
			putchar(char(ch));
	}
	template<typename tp>
	void output(tp x) {
		static char buf[1 << 8];
		int cnt = 0;
		if (x < 0)
			putchar('-'), x = -x;
		do {
			buf[++cnt] = x % 10 | 48;
			x /= 10;
		} while (x);
		while (cnt)
			putchar(buf[cnt--]);
	}
	void output(double x) {
		static char buf[1 << 8];
		int cnt = 0, xn = int(x);
		do {
			buf[cnt++] = xn % 10 | 48;
			xn /= 10;
		} while (xn);
		reverse(buf, buf + cnt);
		buf[cnt++] = '.';
		x = x - int(x);
		fup (t, 1, output_float_digit) {
			x = x * 10;
			buf[cnt++] = int(x) | 48;
			x = x - int(x);
		}
		fup (i, 0, cnt - 1)
			putchar(buf[i]);
	}
	template<typename ...var>
	void output(var &&...args) {
		initializer_list<int>{(output(forward<var>(args)), 0)...};
	}
};
class debuger {
	string delim;
	template<typename tp>
	void print(const tp &x) { cout << x << delim; }
	template<typename tp>
	void print(const vector<tp> &v) { for (auto x : v) cout << x << delim; }
public:
	debuger(string s = " ") : delim(s) {}
	template<typename ...var>
	void operator ()(var &&...args) {
		initializer_list<int>{(print(forward<var>(args)), 0)...};
		cout << endl;
	}
	void msg(const char *fmt, ...) {
		static char buf[1 << 10];
		va_list args;
		va_start(args, fmt);
		vsprintf(buf, fmt, args);
		va_end(args);
		cout << buf << endl;
	}
};
template<typename tp>
class zip {
	using iter = typename vector<tp>::iterator;
public:
	int tot;
	vector<tp> data;
	vector<int> dim;
	zip(const vector<int> &v) {
		dim.resize(v.size());
		copy(it_each(v), dim.begin());
		tot = 1;
		fwn (i, 0, dim.size() - 1) {
			int suf = tot;
			tot *= dim[i];
			dim[i] = suf;
		}
		data.resize(tot);
	}
	template<typename ...var>
	tp &operator ()(var &&...args) {
		assert(sizeof...(args) == dim.size());
		int idx = 0;
		iter it = dim.begin();
		auto product = [](int &ret, iter &it, int val) {
			ret += *it++ * val;
		};
		initializer_list<int>{(product(idx, it, forward<var>(args)), 0)...};
		return data[idx];
	}
	vector<tp> get_dim(int idx) {
		assert(inrange(idx, 0, tot - 1));
		vector<tp> ret(dim.size());
		fup (i, 0, ret.size() - 1) {
			ret[i] = idx / dim[i];
			idx -= ret[i] * dim[i];
		}
		return ret;
	}
};
template<typename tp>
class descrete {
	vector<tp> data;
public:
	descrete(vector<tp> &v) {
		data.assign(it_each(v));
		sort(it_each(data));
		data.erase(unique(it_each(data)), data.end());
		for (auto &x : v)
			x = lower_bound(it_each(data), x) - data.begin();
	}
	tp get(int i) {
		return data[i];
	}
};

#endif

class data {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	direct_io fio;
	debuger bug;
	int n, k, ans;
public:
	data() {
	}
	istream &in() {
		ioend(fio.input(n) && fio.input(k));
		ans = 0;
		fup (t, 1, n) {
			int x;
			fio.input(x);
			if (x % k == 0)
				ans++;
		}
		return cin;
	}
	void deal() {
	}
	void out() {
		fio.output(ans, '\n');
	}
#undef ioend
};

class task {
	int testcase = 1 << 30;
	stringstream tid;
	data gkd{};
public:
	task(
		bool multicase = 0,
		bool testid = 0,
		bool blankline = 0) {
		if (multicase)
			read(testcase);
		for (int ti = 1; ti <= testcase && gkd.in(); ++ti) {
			gkd.deal();
			if (blankline && 1 < ti)
				cout << endl;
			tid << "Case #" << ti << ": ";
			if (testid)
				cout << tid.str();
			gkd.out();
			tid.str("");
		}
	}
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.setf(ios::fixed);
	cout.precision(20);
	task gkd(0, 0, 0);
	return 0;
}
