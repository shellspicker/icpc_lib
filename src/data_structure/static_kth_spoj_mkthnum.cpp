#define FAST_IO 1

#include "template.h"
#include "data_structure/static_kth.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	struct query {
		int l, r, k;
		finput(is, query, o) {
			fio.in(o.l);
			fio.in(o.r);
			fio.in(o.k);
			o.l--, o.r--;
			return is;
		}
	};
	char buf[1024];
	int n, q;
	vector<int> data, ans;
	vector<query> que;
	static_kth<int> dsm;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n) && fio.in(q));
		data.resize(n);
		que.resize(q);
		fup_range (i, 0, n)
			fio.in(data[i]);
		fup_range (i, 0, q)
			cin >> que[i];
		ioend(1);
		return cin;
	}
	void deal() {
		dsm.init(data);
		ans.resize(q);
		fup_range (i, 0, q) {
			query ac = que[i];
			ans[i] = dsm.kth(ac.l, ac.r, ac.k);
		}
	}
	void out() {
		fup_range (i, 0, q)
			fio.msg("%d\n", ans[i]);
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
} gkd;

int main()
{
	return 0;
}