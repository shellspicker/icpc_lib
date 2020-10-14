#define FAST_IO 1

#include "template.h"
#include "data_structure/allocator.h"
#include "data_structure/segment_tree.h"
struct data_info {
	int m1;
	data_info() {}
	data_info(int m) : m1(m) {}
};
struct update_info {
	int v;
	update_info(int v_) : v(v_) {}
};
#define basenode segment_tree_node<data_info, update_info>
struct node : public basenode {
	static node *null;
	node() {}
	node(int l, int r) : basenode(l, r) {}
	virtual void release(update_info *upd) {
		if (upd) {
			meta.m1 = upd->v;
		}
	}
	virtual void pull() {
		if (ls == null || rs == null) {
			meta = ls == null ? rs->meta : ls->meta;
			return;
		}
		meta.m1 = min(ls->meta.m1, rs->meta.m1);
	}
};
node *node::null;
#undef basenode

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
	function<data_info(int)> point = [=](int i) {
		data_info ret{data[i]};
		return ret;
	};
	segment_tree<node, 10233> dsm{point};
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
		dsm.build(0, data.size() - 1);
		ans.clear();
		fup_range (qi, 0, q) {
			command c = cmd[qi];
			if (c.op == 0) {
				auto que_i = dsm.query(c.c.que.l, c.c.que.r);
				ans.push_back(que_i.meta.m1);
			} else {
				update_info upd_i{c.c.upd.v};
				dsm.update(c.c.upd.x, c.c.upd.x, &upd_i);
			}
		}
	}
	void out() {
		for (auto e : ans)
			fio.out(e, '\n');
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
