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
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		return cin;
	}
	void deal() {
	}
	void out() {
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
};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.setf(ios::fixed);
	cout.precision(12);
	task gkd(0, 0, 0);
	return 0;
}
