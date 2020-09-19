#define FAST_IO 1
#include "template.h"
#include "graph/graph.h"
#include "data_structure/dsu.h"
#include "graph/lca_tarjan.h"
#include "basic/idref.h"

struct vif {
	bool vis;
	vector<pair<int, int *>> lca_query;
	vif() {
		lca_query.clear();
	}
};
using graph_t = graph<vif, fake_type>;

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int en, qn;
	idref<string> id;
	graph_t g;
	vector<int> ans;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(en));
		id.init();
		g.resize(en + 1);
		fup_range (i, 0, en) {
			string pp[2];
			int idx[2];
			fup_range (i, 0, 2) {
				fio.in(pp[i]);
				idx[i] = id.get_id(pp[i]);
			}
			g.add(idx[0], idx[1]);
		}
		fio.in(qn);
		ans.resize(qn);
		fup_range (qi, 0, qn) {
			string pp[2];
			int idx[2];
			fup_range (i, 0, 2) {
				fio.in(pp[i]);
				idx[i] = id.get_id(pp[i]);
			}
			fup_range (i, 0, 2)
				g.nodes[idx[i]].meta.lca_query.push_back({idx[i ^ 1], &ans[qi]});
		}
		ioend(1);
		return cin;
	}
	void deal() {
		lca_tarjan(&g, 0);
	}
	void out() {
		fup_range (i, 0, qn)
			fio.msg("%s\n", id.get_orig(ans[i]).data());
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
