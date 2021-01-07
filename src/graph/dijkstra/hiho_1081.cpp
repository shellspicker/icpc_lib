#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#include "graph/dijkstra.h"

struct vif {
	bool vis;
	int dist;
	vif() { vis = 0; dist = inf32; }
};
struct eif {
	int cost;
	eif() {}
	eif(int _1) : cost(_1) {}
};
using graph_t = graph<graph_node<vif>, graph_edge<eif>>;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int gn, gm, gs, gt, ans;
	graph_t grp;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(gn, gm, gs, gt));
		grp.resize(gn);
		gs--, gt--;
		fup (t, 1, gm) {
			int a, b, c;
			fio.in(a, b, c);
			a--, b--;
			grp.add2(a, b, eif(c));
		}
		ioend(1);
		return cin;
	}
	void deal() {
		dijkstra<graph_t> short_path(grp);
		short_path.get<int>(gs);
		ans = grp[gt].meta.dist;
	}
	void out() {
		fio.msg("%d\n", ans);
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
