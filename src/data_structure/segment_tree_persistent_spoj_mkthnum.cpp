#define FAST_IO 1

#include "template.h"
#include "basic/descrete.h"
#include "data_structure/allocator.h"
#define PERSISTENT 1
#include "data_structure/segment_tree.h"
struct data_info {
	int sum;
	data_info() {}
	data_info(int _1) : sum(_1) {}
};
struct update_info {
	int v;
	update_info() {}
	update_info(int _1) : v(_1) {}
};
#define basenode segment_tree_node<data_info, update_info>
struct node : public basenode {
	static node *null;
	node() {}
	node(int l, int r) : basenode(l, r) {}
	virtual void release(update_info *upd) {
		meta.sum += upd->v;
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
	using seg_t = segment_tree<node, 100233>;
	seg_t dsm[100233];
	struct query {
		int l, r, k;
		finput(is, query, o) {
			fio.in(o.l);
			fio.in(o.r);
			fio.in(o.k);
			return is;
		}
	};
	int n, q;
	vector<int> data, ans;
	vector<query> que;
	descrete<int> des;
	function<data_info(int)> point = [](int i) {
		data_info ret{0};
		return ret;
	};
	void preprocess() {
		fio.set_output_float_digit(12);
		seg_t::set_point(point);
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
		seg_t::init();
		dsm[0].build(1, des.size());
		fup_range (i, 0, data.size()) {
			update_info upd{1};
			int pos = i + 1;
			int val = data[i] + 1;
			dsm[pos].update(dsm[pos - 1].root, val, val, &upd);
		}
		ans.resize(q);
		fup_range (i, 0, q) {
			query ac = que[i];
			int idx = dsm[ac.r].query_cnt(dsm[ac.l - 1].root, ac.k).lef - 1;
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
