#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#include "graph/tree_diameter.h"

struct nif {
	bool vis;
	int dist, pre;
	nif() : vis(0) {}
};
using graph_t = graph<nif, fake_type>;
using node = graph_t::node;
using edge = graph_t::edge;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int gn, gm, ans_diam;
	graph_t grp;
	vector<pair<int, int>> ans_add;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(gn, gm));
		grp.resize(gn);
		fup_range (i, 0, gm) {
			int a, b;
			fio.in(a, b);
			a--, b--;
			grp.add2(a, b);
		}
		ioend(1);
		return cin;
	}
	void deal() {
		diameter<graph_t> diam(grp);
		vector<pair<int, int>> center;
		auto mark = [&](int s) {
			node *v;
			edge *e;
			queue<int> que;
			que.push(s);
			while (!que.empty()) {
				int u = que.front();
				que.pop();
				grp[u].meta.vis = 1;
				for (int ei : grp[u].link) {
					tie(v, e) = grp.extend(ei);
					if (v->meta.vis)
						continue;
					que.push(v->id());
				}
			}
		};
		fup_range (u, 0, gn) {
			if (!grp[u].meta.vis) {
				int dm;
				vector<int> path;
				tie(dm, path) = diam.run(u, 1);
				mark(u);
				center.push_back({dm, path[path.size() / 2]});
			}
		}
		sort(it_each(center));
		fup_range (i, 0, center.size() - 1) {
			auto &now = center[i];
			auto &last = center.back();
			grp.add2(now.second, last.second);
			ans_add.push_back({now.second, last.second});
		}
		tie(ans_diam, ignore) = diam.run(0, 0);
	}
	void out() {
		fio.msg("%d\n", ans_diam);
		for (auto &o : ans_add)
			fio.msg("%d %d\n", o.first + 1, o.second + 1);
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
