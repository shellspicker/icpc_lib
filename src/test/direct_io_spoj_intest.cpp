#define FAST_IO 1

#include "template.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int testcase = 1 << 30;
	stringstream tid;
	direct_io fio;
	debuger bug;
	int n, k, ans;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n, k));
		ans = 0;
		fup (t, 1, n) {
			int x;
			fio.in(x);
			if (x % k == 0)
				ans++;
		}
		return cin;
	}
	void deal() {
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
} gkd(0, 0, 0);

int main()
{
	return 0;
}
