#define FAST_IO 1

#include "template.h"
#include "string/sais.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	string s;
	sais sa;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(s));
		return cin;
	}
	void deal() {
		s += '$';
		sa.init(s);
		sa.init_sa();
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
} gkd(0, 0, 0);

int main()
{
	return 0;
}
