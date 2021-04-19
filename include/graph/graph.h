template<typename nif, typename eif>
struct graph {
	struct node {
		static node *base_addr;
		vector<int> link;
		nif meta;
		node() : link(vector<int>()), meta(nif()) {}
		int id() {
			return this - base_addr;
		}
	};
	struct edge {
		int from, to;
		eif meta;
		edge() {}
		edge(int _1, int _2, eif _3 = eif()) : from(_1), to(_2), meta(_3) {}
	};
	vector<node> nodes;
	vector<edge> edges;
	node *&node_base;
	graph(int vn = 0) : node_base(node::base_addr) {
		clear();
		nodes.assign(vn, node());
		node_base = &nodes[0];
		edges.reserve(vn);
	}
	node &operator [](int i) {
		node_base = &nodes[0];
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
	void add(int from, int to, eif meta = eif()) {
		assert(inrange(from, range(0, nodes.size())));
		assert(inrange(to, range(0, nodes.size())));
		add_edge_only(from, to, meta);
		nodes[from].link.push_back(edges.size() - 1);
	}
	void add2(int from, int to, eif meta = eif()) {
		add(from, to, meta);
		add(to, from, meta);
	}
	void add_edge_only(int from, int to, eif meta = eif()) {
		edges.push_back({from, to, meta});
	}
	pair<node *, edge *> extend(int i) {
		pair<node *, edge *> ret;
		ret.first = &nodes[(ret.second = &edges[i])->to];
		return ret;
	}
};
template<typename _1, typename _2>
typename graph<_1, _2>::node *graph<_1, _2>::node::base_addr;

