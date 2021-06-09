#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#define ID 1
#include "graph/heavy_light.h"

struct nif {
	int size, heavy, deep, fa, ac;
	nif() {}
};
struct eif {
	int cost;
	eif() { cost = -1; }
};
using graph_t = graph<nif, eif>;
using node = graph_t::node;
using edge = graph_t::edge;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int gn, gq;
	graph_t grp;
	struct limit {
		int a, b, c;
		bool operator <(const limit &r) const {
			return c > r.c;
		}
	};
	vector<limit> con;
	bool ans_ok;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(gn));
		grp.resize(gn);
		fup_range (t, 0, gn - 1) {
			int a, b;
			fio.in(a, b);
			a--, b--;
			grp.add2(a, b);
		}
		fio.in(gq);
		con.resize(gq);
		for (auto &x : con) {
			fio.in(x.a, x.b, x.c);
			x.a--, x.b--;
		}
		ioend(1);
		return cin;
	}
	void deal() {
		heavy_light<graph_t> hld(grp);
		vector<int> v2e(gn);
		auto set_path = [&](vector<pair<int, int>> &path, int cc) -> bool {
			int m1 = inf32;
			for (auto &seg : path) {
				fup (x, seg.first, seg.second) {
					int ei = v2e[hld.ref[x]];
					auto &e = grp.edges[ei];
					auto &e1 = grp.edges[ei + 1];
					if (e.meta.cost == -1) {
						e.meta.cost = cc;
						e1.meta.cost = cc;
					}
					m1 = min(m1, e.meta.cost);
				}
			}
			return m1 == cc;
		};
		hld.init(0);
		fup_range_s (i, 0, grp.edges.size(), 2) {
			auto &e = grp.edges[i];
			int idx = grp[e.from].meta.deep < grp[e.to].meta.deep ? e.to : e.from;
			v2e[idx] = i;
		}
		sort(it_each(con));
		ans_ok = 1;
		for (auto &x : con) {
			auto path = hld.lca_edge(x.a, x.b);
			if (!set_path(path, x.c)) {
				ans_ok = 0;
				return;
			}
		}
		fup_range (i, 0, grp.edges.size()) {
			auto &e = grp.edges[i];
			if (e.meta.cost == -1)
				e.meta.cost = 1;
		}
	}
	void out() {
		if (ans_ok) {
			fup_range_s (i, 0, grp.edges.size(), 2)
				fio.msg("%d%c", grp.edges[i].meta.cost, " \n"[i == grp.edges.size() - 2]);
		} else {
			fio.msg("-1\n");
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
	new task();
	return 0;
}
