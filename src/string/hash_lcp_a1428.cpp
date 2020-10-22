/*
 * 题意: 给出一堆字符串, 把每个串的后缀拼起来, 求最小字典序的组合.
 *
 * 做法: 从后往前取字符串并且前插, 对于新添加的串的任意2个位置求字典序取最小.
 * 比较字典序, hash二分出最长公共前缀, 再比较下一位.
 * 但是由于hash预处理是后插的, 所以方向要反转一下.
 */
#define FAST_IO 1
#include "template.h"
#include "string/hash.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	ull seed = 3137;
	int strn;
	vector<string> vs;
	string ans;
	precalc_hash hval{3137, 500233};
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		vs.clear();
		ans.clear();
		fio.in(strn);
		vs.resize(strn);
		for (auto &s : vs)
			fio.in(s);
		ioend(1);
		return cin;
	}
	void deal() {
		fwn_range (i, 0, vs.size())
			add(vs[i]);
	}
	void out() {
		fio.out(ans, '\n');
	}
	void add(const string &s) {
		concat(s);
		ans.erase(0, minpos(s));
	}
	void concat(const string &s) {
		string tmp = s;
		reverse(it_each(tmp));
		hval.add(tmp.begin(), tmp.length(), ans.length());
		ans = s + ans;
	}
	int minpos(const string &s) {
		int min = 0, len = ans.length();
		fup_range (i, 0, s.length()) {
			bool cmp;
			tie(ignore, cmp) = hval.lcs(i_rev(len, i), i_rev(len, min), -1);
			if (cmp)
				min = i;
		}
		return min;
	}
public:
	task(
		bool multicase = 0,
		const char *fmt_case = 0,
		bool blankline = 0) {
		static int testcase = 1 << 30;
		static stringstream tid;
		preprocess();
		if (multicase)
			fio.in(testcase);
		for (int ti = 1; ti <= testcase && in(); ++ti) {
			deal();
			if (blankline && 1 < ti)
				fio.out('\n');
			if (fmt_case)
				fio.msg(fmt_case, ti);
			out();
		}
	}
#undef ioend
};

int main()
{
	new task(1);
	return 0;
}
