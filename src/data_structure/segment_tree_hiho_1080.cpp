#define FAST_IO 1

#include "template.h"
#include "data_structure/allocator.h"
#include "data_structure/segment_tree.h"
struct data_info {
	int sum, setv, addv;
	bool set, add;
	data_info() {
		sum = setv = addv = 0;
		set = add = false;
	}
	data_info(int v) : sum(v) {
		setv = addv = 0;
		set = add = false;
	}
};
struct update_info {
	int setv, addv;
	bool set, add;
	update_info() {
		set = add = false;
		setv = addv = 0;
	}
	update_info(int v1, int v2, bool b1, bool b2) :
		setv(v1), addv(v2), set(b1), add(b2) {}
};
#define basenode segment_tree_node<data_info, update_info>
struct node : public basenode {
	static node *null;
	node() {}
	node(int l, int r) : basenode(l, r) {}
	virtual void release(update_info *upd) {
		if (upd->set) {
			meta.sum = length(lef, rig) * upd->setv;
			meta.set = true;
			meta.setv = upd->setv;
			meta.add = false;
			meta.addv = 0;
		}
		if (upd->add) {
			meta.sum += length(lef, rig) * upd->addv;
			meta.add = true;
			meta.addv += upd->addv;
		}
	}
	virtual void push() {
		update_info upd(meta.setv, meta.addv, meta.set, meta.add);
		ls->release(&upd);
		rs->release(&upd);
		meta.set = false;
		meta.add = false;
		meta.addv = 0;
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
	function<data_info(int)> point = [=](int i) {
		return data_info{data[i]};
	};
	segment_tree<node, 100233> dsm{point};
	void preprocess() {
		fio.set_output_float_digit(12);
		decltype(dsm)::init();
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
		dsm.build(0, data.size() - 1);
		ans.clear();
		fup_range (i, 0, q) {
			command c = cmd[i];
			update_info upd;
			if (!c.op) {
				new (&upd) update_info(0, c.add.v, 0, 1);
				dsm.update(c.add.l, c.add.r, &upd);
			} else {
				new (&upd) update_info(c.set.v, 0, 1, 0);
				dsm.update(c.set.l, c.set.r, &upd);
			}
			auto ret = dsm.query(0, data.size() - 1);
			ans.push_back(ret.meta.sum);
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
