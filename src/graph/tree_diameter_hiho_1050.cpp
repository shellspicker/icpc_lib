#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#include "graph/tree_diameter.h"

struct vif {
	int chain;
	bool vis;
	vif() {
		chain = vis = 0;
	}
	vif(int _1, bool _2) : chain(_1), vis(_2) {}
};
struct eif {
	int dist;
	eif() {
		dist = 1;
	}
};
using graph_t = graph<vif, eif>;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int n, ans;
	graph_t g;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n));
		g.resize(n);
		fup (t, 1, n - 1) {
			int a, b;
			fio.in(a, b);
			a--, b--;
			g.add2(a, b);
		}
		ioend(1);
		return cin;
	}
	void deal() {
		ans = tree_diameter(&g);
	}
	void out() {
		fio.out(ans, '\n');
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
