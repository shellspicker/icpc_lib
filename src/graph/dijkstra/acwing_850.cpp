#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#include "graph/dijkstra.h"

struct vif {
	bool vis;
	ll dist;
	vif() { vis = 0; dist = inf64; }
};
struct eif {
	int cost;
	eif() { cost = 0; }
	eif(int _1) : cost(_1) {}
};
using graph_t = graph<graph_node<vif>, graph_edge<eif>>;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int vn, en;
	ll ans;
	graph_t grp;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(vn, en));
		grp.resize(vn);
		fup_range (i, 0, en) {
			int from, to, cost;
			fio.in(from, to, cost);
			from--, to--;
			grp.add(from, to, eif(cost));
		}
		ioend(1);
		return cin;
	}
	void deal() {
		dijkstra<graph_t> short_path(grp);
		short_path.get<ll>(0);
		ans = grp[vn - 1].meta.dist;
		if (ans == inf64)
			ans = -1;
	}
	void out() {
		fio.msg("%lld\n", ans);
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
