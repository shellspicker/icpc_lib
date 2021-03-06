#define FAST_IO 1

#include "template.h"
#define FUNC_RANGE 1
#define FATHER 0
#include "data_structure/treap.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	class query {
	public:
		int l, r;
	};
	vector<query> qa;
	vector<int> ans;
	treap<int, 1, 100233> dsm;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		int dn, qn;
		ioend(fio.in(dn, qn));
		ans.resize(dn);
		iota(it_each(ans), 1);
		qa.resize(qn);
		fup (i, 0, qn - 1) {
			int l, r;
			fio.in(l, r);
			qa[i] = {l, r};
		}
		return cin;
	}
	void deal() {
		dsm.init();
		dsm.build(0, ans);
		for (auto q : qa) {
			dsm.reverse(0, q.l, q.r);
		}
		dsm.print(0, ans);
	}
	void out() {
		fup (i, 0, ans.size() - 1)
			fio.out(ans[i], " \n"[i == ans.size() - 1]);
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
