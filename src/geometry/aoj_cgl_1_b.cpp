#define FAST_IO 1
#include "template.h"
#include "basic/rand.h"
#include "geometry/base.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	pov pt[2];
	int gn;
	vector<pov> vp, ans;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		fio.in(pt[0].x, pt[0].y, pt[1].x, pt[1].y);
		fio.in(gn);
		vp.resize(gn);
		for (auto &o : vp)
			fio.in(o.x, o.y);
		ioend(1);
		return cin;
	}
	void deal() {
		ans.resize(gn);
		fup_range (i, 0, gn)
			ans[i] = segment(pt[0], pt[1]).reflection(vp[i]);
	}
	void out() {
		fup_range (i, 0, ans.size())
			fio.out(ans[i].x, ' ', ans[i].y, '\n');
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
