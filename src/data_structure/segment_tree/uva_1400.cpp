#define FAST_IO 1
#include "template.h"
#include "data_structure/allocator.h"
#include "data_structure/segment_tree.h"

struct subsection {
	int l, r;
	ll v;
	subsection() {}
	subsection(int _1, int _2, ll _3) : l(_1), r(_2), v(_3) {}
	subsection operator +(const subsection &rhs) const {
		subsection ret(l, rhs.r, v + rhs.v);
		return ret;
	}
	bool operator < (const subsection &rhs) const {
		if (v ^ rhs.v)
			return v < rhs.v;
		return make_pair(l, r) > make_pair(rhs.l, rhs.r);
	}
};
struct nif {
	subsection all, pre, suf, sub;
	nif() {}
	nif(subsection _1, subsection _2, subsection _3, subsection _4) :
		all(_1), pre(_2), suf(_3), sub(_4) {}
};
#define base_node segment_tree_node<nif, fake_type, node>
struct node : public base_node {
	node() {}
	node(int l, int r) : base_node(l, r) {}
	void pull() {
		if (ls == null || rs == null) {
			meta = ls == null ? rs->meta : ls->meta;
			return;
		}
		meta.all = ls->meta.all + rs->meta.all;
		meta.pre = max(ls->meta.pre, ls->meta.all + rs->meta.pre);
		meta.suf = max(rs->meta.suf, ls->meta.suf + rs->meta.all);
		meta.sub = max({ls->meta.sub, rs->meta.sub, ls->meta.suf + rs->meta.pre});
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
		int l, r;
		command() {}
		command(int l_, int r_) : l(l_), r(r_) {}
		finput(is, command, o) {
			fio.in(o.l, o.r);
			o.l--;
			o.r--;
			return is;
		}
	};
	vector<command> cmd, ans;
	vector<ll> data;
	segment_tree<node, 500233> sgt;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n, q));
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
		sgt.build(0, data.size() - 1, [&](int i) {
			subsection s(i, i, data[i]);
			return nif{s, s, s, s};
		});
		ans.clear();
		fup_range (i, 0, cmd.size()) {
			command c = cmd[i];
			node fd = sgt.query(c.l, c.r);
			ans.push_back(command(fd.meta.sub.l + 1, fd.meta.sub.r + 1));
		}
	}
	void out() {
		fup_range (i, 0, ans.size())
			fio.msg("%d %d\n", ans[i].l, ans[i].r);
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
	new task(0, "Case %d:\n");
	return 0;
}
