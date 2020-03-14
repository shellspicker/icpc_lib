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
	int x, y;
	string z;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(x, y));
		fio.in(z);
		return cin;
	}
	void deal() {
	}
	void out() {
		fio.out("fio: ", x, '\n');
		cout << "cout: " << x << '\n';
		printf("printf: %d\n", x);
		fio.out("fio: ", y, '\n');
		cout << "cout: " << y << '\n';
		printf("printf: %d\n", y);
		fio.out("fio: ", z, '\n');
		cout << "cout: " << z << '\n';
		printf("printf: %s\n", z.data());
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
