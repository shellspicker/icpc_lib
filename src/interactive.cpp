#define FAST_IO 0
#include "template.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(1);
		return cin;
	}
	void interactive() {
	}
public:
	task(bool multicase = 0) {
		static int testcase = 1 << 30;
		static stringstream tid;
		preprocess();
		if (multicase)
			fio.in(testcase);
		for (int ti = 1; ti <= testcase && in(); ++ti)
			interactive();
	}
#undef ioend
};

int main()
{
	new task();
	return 0;
}
