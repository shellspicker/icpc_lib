#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"

using graph_t = graph<fake_type, fake_type>;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	void preprocess() {
		fio.set_output_float_digit(12);
		graph_t g1, g2;
		g1.resize(10);
		g2.resize(10);
		fup_range (i, 0, 10)
			assert(g1[i].id() == i);
		fup_range (i, 0, 10)
			assert(g2[i].id() == i);
	}
	istream &in() {
		ioend(0);
		ioend(1);
		return cin;
	}
	void deal() {
	}
	void out() {
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
	new task();
	return 0;
}
