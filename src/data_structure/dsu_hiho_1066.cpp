#define FAST_IO 1

#include "template.h"
#include "basic/idref.h"
#include "data_structure/dsu.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	struct cmd {
		int op;
		string name[2];
	};
	int n;
	vector<cmd> ac;
	vector<bool> ans;
	idref<string> id;
	dsu ds;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n));
		ac.resize(n);
		id.init();
		for (auto &in : ac) {
			int op;
			string name[2];
			fio.in(op, name[0], name[1]);
			id.get_id(name[0]);
			id.get_id(name[1]);
			in = cmd{op, name[0], name[1]};
		}
		ioend(1);
		return cin;
	}
	void deal() {
		ds.init(id.cnt());
		ans.clear();
		for (auto q : ac) {
			switch (q.op) {
			case 0:
				ds.link(id.get_id(q.name[0]), id.get_id(q.name[1]));
				break;
			case 1:
				bool same = ds.same(id.get_id(q.name[0]), id.get_id(q.name[1]));
				if (same)
					ans.push_back(1);
				else
					ans.push_back(0);
				break;
			}
		}
	}
	void out() {
		for (auto qa : ans)
			fio.out(qa ? "yes\n" : "no\n");
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
