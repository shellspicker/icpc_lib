// 题意: 给出一堆字符串, 把每个串的后缀拼起来, 求最小字典序的组合.
//
// 做法就是从后往前拼接字符串, hash二分lcp再比较下一位.
// 细节就是hash是从后往前接的, 但是字符串是从前往后算下标的, 主要就是下标计算.
// 正反同时扫描的下标都明确了就简单了, 二分很好写的.
#define FAST_IO 0

#include "template.h"
#include "string/hash.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int testcase = 1 << 30;
	stringstream tid;
	direct_io fio;
	debuger bug;
	ull seed = 3137;
	int strn;
	vector<string> vs;
	string ans;
	vector<ull> hash, exp;
	void concat(const string &s) {
		string tmp = s;
		reverse(it_each(tmp));
		bkdr_hash_preprocess(tmp, hash, seed, ans.length());
		ans = s + ans;
	}
	int minpos(const string &s) {
		int min = 0;
		for (int i = 0; i < s.length(); ++i) {
			int p1, p2, len,
				lo, hi, mid,
				lcp;
			p1 = i, p2 = min, len = ans.length() - max(p1, p2);
			lo = 1, hi = len;
			while (lo <= hi) {
				mid = midpoint(lo, hi);
				if (bkdr_hash_range(hash, exp, range_rev(ans.length(), p1, mid)) ==
						bkdr_hash_range(hash, exp, range_rev(ans.length(), p2, mid)))
					lo = mid + 1;
				else
					hi = mid - 1;
			}
			lcp = hi;
			if (lcp == len) {
				min = max(p1, p2);
			} else {
				if (ans[p1 + lcp] < ans[p2 + lcp])
					min = p1;
				else
					min = p2;
			}
		}
		return min;
	}
	void add(const string &s) {
		concat(s);
		ans.erase(ans.begin(), ans.begin() + minpos(s));
	}
	void preprocess() {
		fio.set_output_float_digit(12);
		exp.resize(500233);
		exp[0] = 1;
		fup (i, 1, 500000) {
			exp[i] = exp[i - 1] * seed;
		}
	}
	istream &in() {
		vs.clear();
		ans.clear();
		fio.in(strn);
		vs.resize(strn);
		fup (i, 0, strn - 1)
			fio.in(vs[i]);
		return cin;
	}
	void deal() {
		for (long i = vs.size() - 1; i >= 0; --i) {
			add(vs[i]);
		}
	}
	void out() {
		fio.out(ans, '\n');
	}
public:
	task(
		bool multicase = 0,
		bool testid = 0,
		bool blankline = 0) {
		preprocess();
		if (multicase)
			fio.in(testcase);
		for (int ti = 1; ti <= testcase && in(); ++ti) {
			deal();
			if (blankline && 1 < ti)
				fio.out('\n');
			tid << "Case #" << ti << ": ";
			if (testid)
				fio.out(tid.str());
			out();
			tid.str("");
		}
	}
#undef ioend
} gkd(1, 0, 0);

int main()
{
	return 0;
}
