#define FAST_IO 1

#include "template.h"
#include "string/sada.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int testcase = 1 << 30;
	stringstream tid;
	direct_io fio;
	debuger bug;
	sada sa;
	string s;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(s));
		return cin;
	}
	void deal() {
		sa.init(s);
	}
	void out() {
		fup (i, 1, sa.sa.size() - 1)
			fio.out(sa.sa[i] + 1, " \n"[i == sa.sa.size() - 1]);
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
