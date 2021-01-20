#define FAST_IO 1
#include "template.h"
#include "data_structure/allocator.h"
#include "data_structure/segment_tree.h"

struct nif {
	int sum, setv, addv;
	bool set, add;
	nif() {
		sum = setv = addv = 0;
		set = add = false;
	}
	nif(int _1) : nif() { sum = _1; }
};
struct uif {
	int setv, addv;
	bool set, add;
	uif() {
		set = add = false;
		setv = addv = 0;
	}
	uif(int v1, int v2, bool b1, bool b2) :
		setv(v1), addv(v2), set(b1), add(b2) {}
};
#define base_node segment_tree_node<nif, uif, node>
struct node : public base_node {
	node() {}
	node(int l, int r) : base_node(l, r) {}
	void release(const uif &ch) {
		if (ch.set) {
			meta.sum = length(lef, rig) * ch.setv;
			meta.setv = ch.setv;
			meta.set = 1;
			meta.add = meta.addv = 0;
		}
		if (ch.add) {
			meta.sum += length(lef, rig) * ch.addv;
			meta.addv += ch.addv;
			meta.add = 1;
		}
	}
	void push() {
		uif ch(meta.setv, meta.addv, meta.set, meta.add);
		ls->release(ch);
		rs->release(ch);
		meta.set = meta.add = meta.addv = 0;
	}
	void pull() {
		meta.sum = ls->meta.sum + rs->meta.sum;
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
				int l, r, v;
			} set;
			struct {
				int l, r, v;
			} add;
		};
		finput(is, command, o) {
			fio.in(o.op);
			if (!o.op) {
				fio.in(o.add.l, o.add.r, o.add.v);
			} else {
				fio.in(o.set.l, o.set.r, o.set.v);
			}
			return is;
		}
	};
	vector<command> cmd;
	vector<int> data, ans;
	segment_tree<node, 100233> sgt;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n, q));
		n++;
		data.resize(n);
		cmd.resize(q);
		fup_range (i, 0, n)
			fio.in(data[i]);
		fup_range (i, 0, q)
			cin >> cmd[i];
		ioend(1);
		return cin;
	}
	void deal() {
		sgt.init();
		sgt.build(0, data.size() - 1, [&](int i) { return nif(data[i]); });
		ans.clear();
		fup_range (i, 0, q) {
			command c = cmd[i];
			uif upd;
			if (!c.op) {
				new (&upd) uif(0, c.add.v, 0, 1);
				sgt.update(c.add.l, c.add.r, upd);
			} else {
				new (&upd) uif(c.set.v, 0, 1, 0);
				sgt.update(c.set.l, c.set.r, upd);
			}
			node ret = sgt.query(0, data.size() - 1);
			ans.push_back(ret.meta.sum);
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
