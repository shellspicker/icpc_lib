#define FAST_IO 1
#include "template.h"
#include "data_structure/rmq.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int n, q;
	vector<int> vc;
	struct query {
		int l, r, ans;
	};
	vector<query> qa;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n));
		vc.resize(n);
		for (auto &x : vc)
			fio.in(x);
		fio.in(q);
		qa.resize(q);
		for (auto &x: qa) {
			fio.in(x.l, x.r);
			x.l--, x.r--;
		}
		ioend(1);
		return cin;
	}
	void deal() {
		auto comb = [=](int a, int b) {
			return min(a, b);
		};
		rmq<int> dsm(comb);
		dsm.init(vc);
		for (auto &x : qa)
			x.ans = dsm.query(x.l, x.r);
	}
	void out() {
		for (auto &x : qa)
			fio.msg("%d\n", x.ans);
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
