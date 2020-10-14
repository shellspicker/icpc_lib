#define FAST_IO 1

#include "template.h"
#include "data_structure/allocator.h"
#define SUB_QUERY 1
#include "data_structure/segment_tree.h"
struct data_info {
	int cnt;
	vector<int> arr;
	data_info() {
		cnt = 0;
		arr.clear();
	}
};
struct query_info {
	int v;
};
#define basenode segment_tree_node<data_info, fake_type, query_info>
struct node : public basenode {
	static node *null;
	node() {}
	node(int l, int r) : basenode(l, r) {}
	virtual void pull() {
		meta.arr.resize(ls->meta.arr.size() + rs->meta.arr.size());
		merge(it_each(ls->meta.arr), it_each(rs->meta.arr), meta.arr.begin());
	}
	virtual void pull(query_info *sbq) {
		if (this == null)
			return;
		if (meta.arr.size()) {
			meta.cnt = lower_bound(it_each(meta.arr), sbq->v) - meta.arr.begin();
		} else {
			meta.cnt = ls->meta.cnt + rs->meta.cnt;
		}
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
			fio.in(o.l);
			fio.in(o.r);
			fio.in(o.k);
			o.l--, o.r--;
			return is;
		}
	};
	char buf[1024];
	int n, q;
	vector<int> data, sor, ans;
	vector<query> que;
	function<data_info(int)> point = [=](int i) {
		data_info ret;
		ret.arr.push_back(data[i]);
		return ret;
	};
	using seg_t = segment_tree<node, 100233>;
	using seg_node_t = node;
	seg_t dsm = seg_t(point);
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n) && fio.in(q));
		data.resize(n);
		que.resize(q);
		fup_range (i, 0, n)
			fio.in(data[i]);
		fup_range (i, 0, q) {
			cin >> que[i];
		}
		ioend(1);
		return cin;
	}
	void deal() {
		dsm.build(0, data.size() - 1);
		sor.assign(it_each(data));
		sort(it_each(sor));
		ans.clear();
		fup_range (i, 0, q) {
			query ac = que[i];
			ans.push_back(kth(ac.l, ac.r, ac.k));
		}
	}
	void out() {
		fup_range (i, 0, q)
			fio.msg("%d\n", ans[i]);
	}
	int kth(int l, int r, int k) {
		int lef, rig, mid;
		query_info sbq;
		lef = 0, rig = sor.size() - 1;
		while (lef <= rig) {
			mid = midpoint(lef, rig);
			sbq.v = sor[mid];
			seg_node_t fd = dsm.query(l, r, &sbq);
			if (fd.meta.cnt < k)
				lef = mid + 1;
			else
				rig = mid - 1;
		}
		return sor[rig];
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
