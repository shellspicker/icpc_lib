#define FAST_IO 1
#include "template.h"
#include "math/exgcd.h"
#include "math/mod.h"
#include "math/comb_num.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	void preprocess() {
		fio.set_output_float_digit(12);
		fup (n, 1, 10) {
			fup (k, 1, n) {
				fio.msg("%llu%c", comb_num_calc(n, k), " \n"[k == n]);
			}
		}
	}
	istream &in() {
		ioend(0);
		return cin;
	}
	void deal() {
	}
	void out() {
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
	new task();
	return 0;
}
