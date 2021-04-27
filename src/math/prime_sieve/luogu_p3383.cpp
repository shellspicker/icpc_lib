#define FAST_IO 1
#include "template.h"
#include "math/prime_sieve.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int gn, gq;
	vector<int> qry, ans;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(gn, gq));
		qry.resize(gq);
		for (auto &x : qry)
			fio.in(x);
		ioend(1);
		return cin;
	}
	void deal() {
		sieve calc(gn);
		calc.run();
		auto &pri = calc.pri;
		ans.resize(gq);
		fup_range (i, 0, gq) {
			int k = qry[i];
			ans[i] = pri[k - 1];
		}
	}
	void out() {
		fup_range (i, 0, gq)
			fio.msg("%d\n", ans[i]);
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
