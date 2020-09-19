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
		finput(is, cmd, o) {
			fio.in(o.op, o.name[0], o.name[1]);
			return is;
		}
	};
	int n;
	vector<cmd> command;
	vector<bool> ans;
	idref<string> id;
	dsu ds;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n));
		command.resize(n);
		id.init();
		fup_range (i, 0, n) {
			cmd &obj = command[i];
			cin >> obj;
			id.get_id(obj.name[0]);
			id.get_id(obj.name[1]);
		}
		ioend(1);
		return cin;
	}
	void deal() {
		ds.init(id.size());
		ans.clear();
		for (auto q : command) {
			if (q.op == 0) {
				ds.link(id.get_id(q.name[0]), id.get_id(q.name[1]));
			} else if (q.op == 1) {
				bool same = ds.same(id.get_id(q.name[0]), id.get_id(q.name[1]));
				ans.push_back(same);
			}
		}
	}
	void out() {
		for (auto qa : ans)
			fio.msg("%s\n", qa ? "yes" : "no");
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
