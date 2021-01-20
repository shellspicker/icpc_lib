#define FAST_IO 1
#include "template.h"
#include "data_structure/segment_tree_fixed.h"

struct nif {
	int sum, setv;
	bool set;
	nif() { sum = setv = set = 0; }
	nif(int _1) : nif() { sum = _1; }
};
struct uif {
	int v;
	uif() {}
	uif(int _1) : v(_1) {}
};
using base_node = segment_tree_node<nif, uif>;
class segment_tree : public base_node {

	void release(int l, int r, const uif &c) {
		node &o = mem[seg_id(l, r)];
		o.meta.sum = c.v * length(l, r);
		o.meta.setv = c.v;
		o.meta.set = 1;
	}
	void push(int l, int r) {
		int m = midpoint(l, r);
		node &o = mem[seg_id(l, r)];
		if (o.meta.set) {
			uif tc(o.meta.setv);
			release(l, m - 1, tc);
			release(m, r, tc);
			o.meta.set = 0;
		}
	}
	node pull(const node &l, const node &r) {
		node ret;
		ret.meta.sum = l.meta.sum + r.meta.sum;
		return ret;
	}
};

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
		sgt.build([&](int i) { return nif(data[i]); });
		ans.clear();
		fup_range (i, 0, q) {
			command c = cmd[i];
			if (!c.op) {
				node que = sgt.query(c.que.l, c.que.r);
				ans.push_back(que.meta.sum);
			} else {
				uif upd{c.upd.v};
				sgt.update(c.upd.l, c.upd.r, upd);
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
