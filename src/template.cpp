#define FAST_IO 1
#include "template.h"

class task {
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
#define ioend(cond) \
		do {\
			if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
		} while(0)
		ioend(1);
		return cin;
#undef ioend
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
};

int main()
{
	new task();
	return 0;
}
