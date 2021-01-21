#define FAST_IO 1

#include "template.h"
#include "basic/descrete.h"
#include "data_structure/allocator.h"
#define PERSISTENT 1
#include "data_structure/segment_tree.h"

struct nif {
	int sum;
	nif() {}
	nif(int _1) : sum(_1) {}
};
struct uif {
	int v;
	uif() {}
	uif(int _1) : v(_1) {}
};
#define base_node segment_tree_node<nif, uif, node>
struct node : public base_node {
	static node *null;
	node() {}
	node(int l, int r) : base_node(l, r) {}
	void release(const uif &ch) {
		meta.sum += ch.v;
	}
	void pull() {
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
	struct query {
		int l, r, k;
		finput(is, query, o) {
			fio.in(o.l, o.r, o.k);
			return is;
		}
	};
	int n, q;
	vector<int> data, ans;
	vector<query> que;
	descrete<int> des;
	segment_tree<node, 100233> sgt[100233];
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n) && fio.in(q));
		data.resize(n);
		que.resize(q);
		fup_range (i, 0, n)
			fio.in(data[i]);
		fup_range (i, 0, q)
			cin >> que[i];
		ioend(1);
		return cin;
	}
	void deal() {
		des.init(data);
		sgt[0].init();
		sgt[0].build(1, des.size(), [&](int i) {
				return nif(0);
		});
		fup_range (i, 0, data.size()) {
			uif upd(1);
			int pos = i + 1, val = data[i] + 1;
			sgt[pos].update(sgt[pos - 1].root, val, val, upd);
		}
		ans.resize(q);
		fup_range (i, 0, q) {
			query ac = que[i];
			int idx = sgt[ac.r].query_cnt(sgt[ac.l - 1].root, ac.k).lef - 1;
			ans[i] = des.get(idx);
		}
	}
	void out() {
		fup_range (i, 0, q)
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
