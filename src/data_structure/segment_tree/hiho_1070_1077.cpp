#define FAST_IO 1
#include "template.h"
#include "data_structure/allocator.h"
#include "data_structure/segment_tree.h"

struct nif {
	int m1;
	nif() : m1(inf32) {}
	nif(int m) : m1(m) {}
};
struct uif {
	int v;
	uif(int v_) : v(v_) {}
};
#define base_node segment_tree_node<nif, uif, node>
struct node : public base_node {
	node() {}
	node(int l, int r) : base_node(l, r) {}
	void release(const uif &upd) {
		meta.m1 = upd.v;
	}
	void pull() {
		meta.m1 = min(ls->meta.m1, rs->meta.m1);
	}
};
#undef base_node

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
		};
		finput(is, command, o) {
			fio.in(o.op);
			if (o.op == 0) {
				fio.in(o.que.l, o.que.r);
				o.que.l--;
				o.que.r--;
			} else {
				fio.in(o.upd.x, o.upd.v);
				o.upd.x--;
			}
			return is;
		}
	};
	vector<command> cmd;
	vector<int> data, ans;
	segment_tree<node, 1000233> dsm;
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
		decltype(dsm)::init();
		dsm.build(0, data.size() - 1, [&](int i) { return nif(data[i]); });
		ans.clear();
		fup_range (qi, 0, q) {
			command c = cmd[qi];
			if (c.op == 0) {
				node que_i = dsm.query(c.que.l, c.que.r);
				ans.push_back(que_i.meta.m1);
			} else {
				uif upd_i{c.upd.v};
				dsm.update(c.upd.x, c.upd.x, upd_i);
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
