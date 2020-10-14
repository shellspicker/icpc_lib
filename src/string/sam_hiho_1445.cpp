#define FAST_IO 1
#include "template.h"
#include "string/sam.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	function<int(char)> sam_idx = [=](char ch) {
		return ch - 'a';
	};
	sam<1000233, 26> dsm{sam_idx};
	string text;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(text));
		ioend(1);
		return cin;
	}
	void deal() {
		dsm.build(text);
	}
	void out() {
		fio.msg("%lld\n", dsm.substr_cnt());
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
} gkd;

int main()
{
	return 0;
}
