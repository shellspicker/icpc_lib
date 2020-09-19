#pragma once

#pragma message \
usage_begin("graph.h") \
line("synopsis:") \
line("\tstruct graph<v_info, e_info>;") \
line("\tv_info: 结点信息.") \
line("\t\t自定义的结构体.") \
line("\te_info: 边信息.") \
line("\t\t自定义的结构体.") \
line("\t\t空构造函数写好默认边信息, 加边函数省略参数用.") \
line("public member:") \
line("\tvector<node> nodes;") \
line("\tvector<edge> edges;") \
line("public function:") \
line("\tvoid add(int, int, e_info);") \
line("\tvoid add2(int, int, e_info);") \
line("\tvoid resize(int);") \
line("\tvoid clear();") \
line("\tpair<node *, edge *> extend(int);") \
usage_end()

template<typename v_info, typename e_info>
struct graph {
	struct edge;
	struct node {
		int id;
		vector<int> link;
		v_info meta;
		node() {}
		node(int _1) : id(_1) {
			link.clear();
		}
	};
	struct edge {
		int from, to;
		e_info meta;
		edge() {}
		edge(int _1, int _2, e_info _3) : from(_1), to(_2), meta(_3) {}
	};
	vector<node> nodes;
	vector<edge> edges;
	graph(int vn = 0) {
		clear();
		nodes.resize(vn);
		edges.reserve(vn);
		fup_range (i, 0, vn)
			new (&nodes[i]) node(i);
	}
	pair<node *, edge *> extend(int i) {
		pair<node *, edge *> ret;
		ret.first = &nodes[(ret.second = &edges[i])->to];
		return ret;
	}
	void clear() {
		nodes.clear();
		edges.clear();
	}
	void resize(int vn) {
		new (this) graph(vn);
	}
	void add(int from, int to, e_info e_if = e_info()) {
		assert(inrange(from, range(0, nodes.size())));
		assert(inrange(to, range(0, nodes.size())));
		edges.push_back({from, to, e_if});
		nodes[from].link.push_back(edges.size() - 1);
	}
	void add2(int from, int to, e_info e_if = e_info()) {
		add(from, to, e_if);
		add(to, from, e_if);
	}
};
