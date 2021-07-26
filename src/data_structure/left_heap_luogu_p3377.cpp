#define FAST_IO 1
#include "template.h"
#include "data_structure/allocator.h"
#include "data_structure/left_heap.h"
#include "basic/rand.h"
#include "data_structure/dsu.h"

#define base left_heap_node<lnode, pair<int, int>>
struct lnode : base {
	lnode() {}
	lnode(pair<int, int> x) : base(x) {}
	void pull() {
		base::pull();
	}
};
#undef base

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int gn, gq;
	left_heap<lnode, less> heap;
	struct query {
		int type;
		union {
			struct {
				int a, b;
			} mer;
			struct {
				int x;
			} que;
		};
	};
	vector<int> da;
	vector<query> cmd;
	vector<int> ans;
	dsu cc;
	void preprocess() {
		fio.set_output_float_digit(12);
		heap.resize(100233, 100233);
	}
	istream &in() {
		ioend(fio.in(gn, gq));
		da.resize(gn);
		for (auto &x : da)
			fio.in(x);
		cmd.resize(gq);
		for (auto &c : cmd) {
			fio.in(c.type);
			if (c.type == 1) {
				fio.in(c.mer.a, c.mer.b);
				c.mer.a--, c.mer.b--;
			} else {
				fio.in(c.que.x);
				c.que.x--;
			}
		}
		ioend(1);
		return cin;
	}
	void deal() {
		vector<bool> rm(gn);
		cc.init(gn);
		heap.init();
		ans.clear();
		fup_range (i, 0, gn) {
			heap.push(i, {da[i], i});
		}
		for (auto &c : cmd) {
			if (c.type == 1) {
				int a, b;
				a = c.mer.a;
				b = c.mer.b;
				if (rm[a] || rm[b] || cc.same(a, b))
					continue;
				cc.id(a, b);
				auto com = heap.merge(a, b);
				comb_helper(heap, cc, com, a, b);
			} else {
				int id = c.que.x;
				if (rm[id]) {
					ans.push_back(-1);
				} else {
					cc.id(id);
					auto top = heap.top(id);
					ans.push_back(top->key.first);
					heap.pop(id);
					rm[heap(top)] = 1;
				}
			}
		}
	}
	void out() {
		for (auto &x : ans)
			fio.msg("%d\n", x);
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
