#define FAST_IO 1

#include "template.h"
#define FUNC_AM 1
#define AM_COMPLETE 0
#define FIND_MODE TABLE
#include "string/ac_am.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	ac_am<1000233> dsm{[](char ch){ return ch - 'a'; }};
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		int n;
		ioend(fio.in(n));
		dsm.init();
		fup (i, 1, n) {
			string s;
			fio.in(s);
			dsm.insert(s);
		}
		dsm.build();
		string text;
		fio.in(text);
		dsm.find(text);
		if (dsm.is_find)
			fio.out("YES\n");
		else
			fio.out("NO\n");
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
