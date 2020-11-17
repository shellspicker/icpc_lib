#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#include "graph/bellman_ford.h"

struct eif {
	ll cost;
	eif() { cost = 0; }
	eif(ll _1) : cost(_1) {}
};
using graph_t = graph<fake_type, eif>;
using node = graph_t::node;
using edge = graph_t::edge;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int vn, en, ss;
	vector<ll> ans;
	graph_t g;
	bellman_ford<graph_t> minpath{&g};
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(vn, en, ss));
		ss--;
		g.resize(vn);
		fup_range (i, 0, en) {
			int from, to;
			ll cost;
			fio.in(from, to, cost);
			from--, to--;
			g.add(from, to, eif(cost));
		}
		ioend(1);
		return cin;
	}
	void deal() {
		ans = get<1>(minpath.get<ll>(ss));
		fup_range (i, 0, ans.size())
			if (ans[i] == get_inf<ll>())
				ans[i] = 2147483647;
	}
	void out() {
		fup_range (i, 0, ans.size())
			fio.msg("%lld%c", ans[i], " \n"[i == ans.size() - 1]);
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