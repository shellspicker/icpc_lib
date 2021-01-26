#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#define BFS 1
#include "graph/topo.h"

struct nif {
	int in, pos;
	nif() {
		in = 0;
	}
};
using graph_t = graph<graph_node<nif>, graph_edge<fake_type>>;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	graph_t grp;
	bool ok;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		int n, m;
		fio.in(n, m);
		grp.resize(n);
		fup_range (t, 0, m) {
			int d, a, b;
			fio.in(d, a, b);
			a--, b--;
			if (d) {
				grp.add(a, b);
				grp[b].meta.in++;
			} else {
				grp.add_edge_only(a, b);
			}
		}
		ioend(1);
		return cin;
	}
	void deal() {
		topo_bfs<graph_t> tp_sort(grp);
		tie(ok, ignore) = tp_sort.get();
	}
	void out() {
		if (ok) {
			fio.msg("YES\n");
			fup_range (i, 0, grp.edges.size()) {
				auto &e = grp.edges[i];
				auto &from = grp[e.from].meta;
				auto &to = grp[e.to].meta;
				if (from.pos < to.pos)
					fio.msg("%d %d\n", e.from + 1, e.to + 1);
				else
					fio.msg("%d %d\n", e.to + 1, e.from + 1);
			}
		} else {
			fio.msg("NO\n");
		}
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
	new task(1);
	return 0;
}
