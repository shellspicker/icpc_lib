#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#include "graph/heavy_light.h"

struct nif {
	int size, heavy, deep, fa, ac;
	ll dist;
	nif() {}
};
struct eif {
	int cost;
	eif() {}
	eif(int _1) : cost(_1) {}
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
	struct ask {
		int a, b;
		ll ans;
	};
	vector<ask> qry;
	void preprocess() {
	}
	istream &in() {
		fio.in(gn, gq);
		grp.resize(gn);
		qry.resize(gq);
		fup_range (t, 0, gn - 1) {
			int a, b, c;
			fio.in(a, b, c);
			a--, b--;
			grp.add2(a, b, eif(c));
		}
		for (auto &q : qry) {
			fio.in(q.a, q.b);
			q.a--, q.b--;
		}
		ioend(1);
		return cin;
	}
	void deal() {
		heavy_light<graph_t> hld(grp);
		dfs(0, -1, 0);
		hld.init(0);
		for (auto &q : qry)
			q.ans = grp[q.a].meta.dist + grp[q.b].meta.dist - 2 * grp[hld.lca(q.a, q.b)].meta.dist;
	}
	void out() {
		for (auto &q : qry)
			fio.msg("%d\n", q.ans);
	}
	void dfs(int u, int f, ll dist) {
		node *v;
		edge *e;
		auto &mt = grp[u].meta;
		mt.dist = dist;
		for (int ei : grp[u].link) {
			tie(v, e) = grp.extend(ei);
			if (v->id() == f)
				continue;
			dfs(v->id(), u, dist + e->meta.cost);
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
