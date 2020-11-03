#define FAST_IO 1
#include "template.h"
#include "data_structure/rmq.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	class query {
	public:
		int l, r, ans;
	};
	vector<int> v;
	vector<query> qa;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		int vn, qn;
		ioend(fio.in(vn, qn));
		v.resize(vn);
		fup_range (i, 0, vn)
			fio.in(v[i]);
		qa.resize(qn);
		fup_range (i, 0, qn) {
			int l, r;
			fio.in(l, r);
			l--, r--;
			qa[i] = {l, r, 0};
		}
		return cin;
	}
	void deal() {
		auto comb = [](int a, int b) {
			return max(a, b);
		};
		rmq<int> dsm{comb};
		dsm.init(v);
		for (auto &q : qa)
			q.ans = dsm.query(q.l, q.r);
	}
	void out() {
		for (auto &q : qa)
			fio.out(q.ans, '\n');
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
};

int main()
{
	new task();
	return 0;
}
