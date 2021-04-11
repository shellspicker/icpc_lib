#define FAST_IO 1
#include "template.h"
#include "string/kmp.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	string text, pattern;
	int ans;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		fio.in(pattern, text);
		ioend(1);
		return cin;
	}
	void deal() {
		ans = kmp::search(text.begin(), text.size(), pattern.begin(), pattern.size()).size();
	}
	void out() {
		fio.msg("%d\n", ans);
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
	new task(1);
	return 0;
}
