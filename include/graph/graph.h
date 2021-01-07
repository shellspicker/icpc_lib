template<typename info>
struct graph_node {
	typedef info info_t;
	static graph_node *base_addr;
	vector<int> link;
	info meta;
	graph_node() : link(vector<int>()), meta(info()) {}
	int id() {
		return this - base_addr;
	}
};
template<typename _1>
graph_node<_1> *graph_node<_1>::base_addr;

template<typename info>
struct graph_edge {
	typedef info info_t;
	int from, to;
	info meta;
	graph_edge() {}
	graph_edge(int _1, int _2, info _3 = info()) : from(_1), to(_2), meta(_3) {}
};

template<typename node, typename edge>
struct graph {
	typedef node node_t;
	typedef edge edge_t;
	typedef typename node::info_t nif;
	typedef typename edge::info_t eif;
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

