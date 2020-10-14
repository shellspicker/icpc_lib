#pragma once

#define GRAPH_T template<typename _1, typename _2>
#define GRAPH_C graph<_1, _2>
#define GRAPH_NODE_T GRAPH_C::node
#define GRAPH_NODE_C typename GRAPH_NODE_T

template<typename v_info, typename e_info>
struct graph {
	struct node {
		static node *baseaddr;
		vector<int> link;
		v_info meta;
		node() : link(vector<int>()), meta(v_info()) {}
		int id() {
			return this - baseaddr;
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
	node *&baseaddr = node::baseaddr;
	graph(int vn = 0) {
		clear();
		nodes.assign(vn, node());
		baseaddr = &nodes[0];
		edges.reserve(vn);
	}
	node &operator [](int i) {
		return nodes[i];
	}
	void clear() {
		nodes.clear();
		edges.clear();
	}
	int size() {
		return nodes.size();
	}
	void resize(int vn) {
		new (this) graph(vn);
	}
	void add(int from, int to, e_info e_if = e_info()) {
		assert(inrange(from, range(0, nodes.size())));
		assert(inrange(to, range(0, nodes.size())));
		add_edge_only(from, to, e_if);
		nodes[from].link.push_back(edges.size() - 1);
	}
	void add2(int from, int to, e_info e_if = e_info()) {
		add(from, to, e_if);
		add(to, from, e_if);
	}
	void add_edge_only(int from, int to, e_info e_if = e_info()) {
		edges.push_back({from, to, e_if});
	}
	pair<node *, edge *> extend(int i) {
		pair<node *, edge *> ret;
		ret.first = &nodes[(ret.second = &edges[i])->to];
		return ret;
	}
};
GRAPH_T
GRAPH_NODE_C *GRAPH_NODE_T::baseaddr;

#undef GRAPH_T
#undef GRAPH_C
#undef GRAPH_NODE_T
#undef GRAPH_NODE_C
