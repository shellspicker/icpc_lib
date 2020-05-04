/*
 * 正序求最大表示的第一个位置, 逆序求最大表示的最后一个位置.
 */
#define FAST_IO 1

#include "template.h"
#include "string/lexico_rotate.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int len;
	string text, rev;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(len, text));
		return cin;
	}
	void deal() {
	}
	void out() {
		rev = text;
		auto cw = lexico_rotate<greater<int>>(text, 1);
		reverse(it_each(rev));
		auto ccw = lexico_rotate<greater<int>>(rev, 0);
		ccw.first = i_rev(len, ccw.first);
		int lexico = cw.second.compare(ccw.second);
		if (lexico >= 0) {
			if (!lexico && ccw.first < cw.first) {
				fio.out(ccw.first + 1, ' ', 1, '\n');
			} else {
				fio.out(cw.first + 1, ' ', 0, '\n');
			}
		} else {
			fio.out(ccw.first + 1, ' ', 1, '\n');
		}
		return;
	}
public:
	task(
		bool multicase = 0,
		bool testid = 0,
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
			if (testid) {
				tid << "Case #" << ti << ": ";
				fio.out(tid.str());
				tid.str("");
			}
			out();
		}
	}
#undef ioend
} gkd(1, 0, 0);

int main()
{
	return 0;
}
