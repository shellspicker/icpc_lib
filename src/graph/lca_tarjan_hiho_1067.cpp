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
	struct command {
		int pp[2], ans;
	};
	vector<command> cmd;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		auto input = [&](command &c) {
			string name[2];
			fio.in(name[0], name[1]);
			c.pp[0] = id.get_id(name[0]);
			c.pp[1] = id.get_id(name[1]);
			fup_range (i, 0, 2)
				g[c.pp[i]].meta.lca_query.push_back({c.pp[i ^ 1], &c.ans});
		};
		ioend(fio.in(en));
		id.init();
		g.resize(en + 1);
		fup_range (i, 0, en) {
			command tmp;
			input(tmp);
			g.add(tmp.pp[0], tmp.pp[1]);
		}
		fio.in(qn);
		cmd.resize(qn);
		for_each(it_each(cmd), input);
		ioend(1);
		return cin;
	}
	void deal() {
		lca_tarjan(&g, &g[0]);
	}
	void out() {
		auto output = [&](command &c) {
			fio.msg("%s\n", id.get_orig(c.ans).data());
		};
		for_each(it_each(cmd), output);
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
