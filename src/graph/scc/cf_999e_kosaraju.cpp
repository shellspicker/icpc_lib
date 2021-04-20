#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#include "graph/graph_reverse.h"
#include "graph/scc_kosaraju.h"

struct vif {
	bool vis;
	int gid, ind;
	vif() : ind(0) {}
};
using graph_t = graph<vif, fake_type>;
using node = graph_t::node;
using edge = graph_t::edge;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int gn, gm, gs, ans;
	graph_t grp;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(gn, gm, gs));
		gs--;
		grp.resize(gn);
		fup_range (t, 0, gm) {
			int a, b;
			fio.in(a, b);
			a--, b--;
			grp.add(a, b);
		}
		ioend(1);
		return cin;
	}
	void deal() {
		scc_kosaraju<graph_t> scc(grp);
		auto ret = scc.run();
		vector<vector<int>> &scc_group = get<0>(ret);
		graph_t &g_shrink = get<1>(ret);
		fup_range (i, 0, g_shrink.edges.size()) {
			auto &e = g_shrink.edges[i];
			g_shrink[e.to].meta.ind++;
		}
		if (!g_shrink[grp[gs].meta.gid].meta.ind)
			g_shrink[grp[gs].meta.gid].meta.ind++;
		ans = 0;
		fup_range (u, 0, g_shrink.size())
			if (!g_shrink[u].meta.ind)
				ans++;
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
