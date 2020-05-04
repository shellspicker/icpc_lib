/*
 * 最大表示, 下标不连续.
 */
#define FAST_IO 1

#include "template.h"
#define STEP 1
#include "string/lexico_rotate.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int len;
	string text;
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
		auto nxt = [=](int i) -> int {
			return (1ll * i * i + 1) % len;
		};
		auto ans = lexico_rotate<23, greater<int>>(text, 1, nxt);
		fio.out(ans.second, '\n');
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
} gkd(1, 1, 0);

int main()
{
	return 0;
}
