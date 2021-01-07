#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#include "graph/bellman_ford.h"

struct vif {
	bool inq;
	int cnt, dist;
	vif() { inq = 0; cnt = 0; dist = inf32; }
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
	int vn, en, ans;
	graph_t grp;
	bool ok;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(vn, en));
		grp.resize(vn);
		fup (t, 1, en) {
			int a, b, c;
			fio.in(a, b, c);
			a--, b--;
			grp.add(a, b, eif(c));
		}
		ioend(1);
		return cin;
	}
	void deal() {
		bellman_ford<graph_t> short_path(grp);
		ok = !short_path.get<int>(0);
		if (ok)
			ans = grp[vn - 1].meta.dist;
		if (ans == inf32)
			ok = 0;
	}
	void out() {
		if (ok)
			fio.msg("%d\n", ans);
		else
			fio.msg("impossible\n");
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
