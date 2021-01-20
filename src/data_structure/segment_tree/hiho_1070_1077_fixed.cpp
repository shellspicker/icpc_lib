#define FAST_IO 1
#include "template.h"
#include "data_structure/segment_tree_fixed.h"

struct nif {
	int m1;
	nif() : m1(inf32) {}
	nif(int _1) : m1(_1) {}
};
struct uif {
	int v;
	uif() {}
	uif(int _1) : v(_1) {}
};
typedef segment_tree_node<nif, uif> node;
class segment_tree : public segment_tree_base<node> {
	void release(node &o, const uif &u) {
		o.meta.m1 = u.v;
	}
	node pull(const node &ls, const node &rs) {
		node ret;
		ret.meta.m1 = min(ls.meta.m1, rs.meta.m1);
		return ret;
	}
};

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int n, q;
	struct command {
		int op;
		union {
			struct {
				int x, v;
			} upd;
			struct {
				int l, r;
			} que;
		} c;
		finput(is, command, o) {
			fio.in(o.op);
			if (o.op == 0) {
				fio.in(o.c.que.l, o.c.que.r);
				o.c.que.l--;
				o.c.que.r--;
			} else {
				fio.in(o.c.upd.x, o.c.upd.v);
				o.c.upd.x--;
			}
			return is;
		}
	};
	vector<command> cmd;
	vector<int> data, ans;
	segment_tree sgt;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n));
		data.resize(n);
		fup_range (i, 0, n)
			fio.in(data[i]);
		fio.in(q);
		cmd.resize(q);
		fup_range (i, 0, q)
			cin >> cmd[i];
		ioend(1);
		return cin;
	}
	void deal() {
		sgt.init(0, data.size() - 1);
		sgt.build([=](int i) { return nif(data[i]); });
		ans.clear();
		fup_range (qi, 0, q) {
			command c = cmd[qi];
			if (c.op == 0) {
				node que_i = sgt.query(c.c.que.l, c.c.que.r);
				ans.push_back(que_i.meta.m1);
			} else {
				uif upd_i{c.c.upd.v};
				sgt.update(c.c.upd.x, c.c.upd.x, upd_i);
			}
		}
	}
	void out() {
		fup_range (i, 0, ans.size())
			fio.msg("%d\n", ans[i]);
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
