#define FAST_IO 1
#include "template.h"
#include "math/prime_sieve.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int gn;
	vector<int> qry, ans;
	void preprocess() {
		fio.set_output_float_digit(12);
		factor_sum calc(10000000);
		calc.run();
		auto &sum = calc.sum;
		ans.assign(10000001, -1);
		fup_range (x, 1, 10000000) {
			int s = sum[x];
			if (10000000 < s)
				continue;
			if (ans[s] == -1)
				ans[s] = x;
		}
	}
	istream &in() {
		ioend(fio.in(gn));
		qry.resize(gn);
		for (auto &x : qry)
			fio.in(x);
		ioend(1);
		return cin;
	}
	void deal() {
	}
	void out() {
		for (auto &x : qry)
			fio.msg("%d\n", ans[x]);
	}
public:
	task(
		bool multicase = 0,
		const char *fmt_case = 0,
		bool blankline = 0) {
		static int testcase = 1 << 30;
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
	new task();
	return 0;
}
