#define FAST_IO 1
#include "template.h"
#include "basic/rand.h"
#include "geometry/base.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	pov v0;
	int gq;
	struct query {
		pov v;
		int ans;
	};
	vector<query> qry;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		double p[4];
		ioend(fio.in(p[0], p[1], p[2], p[3]));
		v0 = pov(p[2], p[3]) - pov(p[0], p[1]);
		fio.in(gq);
		qry.resize(gq);
		for (auto &o : qry) {
			fio.in(p[2], p[3]);
			o.v = pov(p[2], p[3]) - pov(p[0], p[1]);
		}
		ioend(1);
		return cin;
	}
	void deal() {
		for (auto &o : qry)
			o.ans = v0.ccw(o.v);
	}
	void out() {
		for (auto &o : qry) {
			if (o.ans == 0) {
				fio.msg("COUNTER_CLOCKWISE\n");
			} else if (o.ans == 1) {
				fio.msg("CLOCKWISE\n");
			} else if (o.ans == 2) {
				fio.msg("ONLINE_BACK\n");
			} else if (o.ans == 3) {
				fio.msg("ONLINE_FRONT\n");
			} else if (o.ans == 4) {
				fio.msg("ON_SEGMENT\n");
			}
		}
	}
public:
	task(
		bool multicase = 0,
		const char *fmt_case = 0,
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
