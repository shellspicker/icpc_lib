#define FAST_IO 1

#include "template.h"
#include "data_structure/allocator.h"
#include "data_structure/segment_tree.h"
struct data_info {
	int sum, setv;
	bool set;
	data_info() : sum(0), setv(0), set(false) {}
	data_info(int v) : sum(v), setv(0), set(false) {}
	data_info(int v1, int v2, bool b) : sum(v1), setv(v2), set(b) {}
};
struct update_info {
	int v;
	update_info() {}
	update_info(int v_) : v(v_) {}
};
#define basenode segment_tree_node<data_info, update_info>
struct node : public basenode {
	static node *null;
	node() {}
	node(int l, int r) : basenode(l, r) {}
	virtual void release(update_info *upd) {
		if (upd) {
			meta.sum = length(lef, rig) * upd->v;
			meta.set = true;
			meta.setv = upd->v;
		}
	}
	virtual void push() {
		if (meta.set) {
			update_info upd(meta.setv);
			ls->release(&upd);
			rs->release(&upd);
			meta.set = false;
		}
	}
	virtual void pull() {
		if (ls == null || rs == null) {
			meta = ls == null ? rs->meta : ls->meta;
			return;
		}
		meta.sum = ls->meta.sum + rs->meta.sum;
	}
};
node *node::null;
#undef basenode

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	struct command {
		int op;
		union {
			struct {
				int l, r, v;
			} upd;
			struct {
				int l, r;
			} que;
		};
		finput(is, command, o) {
			fio.in(o.op);
			if (!o.op) {
				fio.in(o.que.l, o.que.r);
				o.que.l--;
				o.que.r--;
			} else {
				fio.in(o.upd.l, o.upd.r, o.upd.v);
				o.upd.l--;
				o.upd.r--;
			}
			return is;
		}
	};
	int n, q;
	vector<int> data, ans;
	vector<command> cmd;
	function<data_info(int)> point = [=](int i) {
		return data_info{data[i]};
	};
	segment_tree<node, 100233> dsm{point};
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
		fup_range (i, 0, q) {
			command c = cmd[i];
			if (!c.op) {
				auto que = dsm.query(c.que.l, c.que.r);
				ans.push_back(que.meta.sum);
			} else {
				update_info upd{c.upd.v};
				dsm.update(c.upd.l, c.upd.r, &upd);
			}
		}
	}
	void out() {
		fup_range (i, 0, ans.size())
			fio.out(ans[i], '\n');
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
