#define NODE_C typename graph::node
#define EDGE_C typename graph::edge

template<typename graph>
struct heavy_light {
	using node = NODE_C;
	using edge = EDGE_C;

	graph *g;
	node *nd;
#if ID
	vector<int> id;
#endif

	heavy_light(graph *_1) :
		g(_1), nd(&g->nodes[0]) {}

	void init(node *root) {
#if ID
		int clk;
#endif
		function<void(node *, int, int)> dfs = [&](node *u, int f, int lev) {
			node *v;
			edge *e;
			auto &mt = u->meta;
			mt.size = 1;
			mt.heavy = -1;
			mt.deep = lev;
			mt.fa = f;
			for (int ei : u->link) {
				tie(v, e) = g->extend(ei);
				if (v->id() == f)
					continue;
				dfs(v, u->id(), lev + 1);
				mt.size += v->meta.size;
				if (!~mt.heavy || mt.heavy[nd].meta.size < v->meta.size)
					mt.heavy = v->id();
			}
		};
		function<void(node *, int)> make = [&](node *u, int chain) {
			node *v;
			edge *e;
			auto &mt = u->meta;
			mt.ac = chain;
#if ID
			id[u->id()] = clk++;
#endif
			if (!~mt.heavy)
				return;
			make(&mt.heavy[nd], chain);
			for (int ei : u->link) {
				tie(v, e) = g->extend(ei);
				if (v->id() == mt.fa || v->id() == mt.heavy)
					continue;
				make(v, v->id());
			}
		};
		function<void()> get_id = [&]() {
#if ID
			clk = 0;
			id.resize(g->size());
#endif
			make(root, root->id());
		};
		dfs(root, -1, 0);
		get_id();
	}

	node *lca(node *low, node *high) {
		while (low->meta.ac != high->meta.ac) {
			if (low->meta.ac[nd].meta.deep < high->meta.ac[nd].meta.deep)
				swap(low, high);
			low = &low->meta.ac[nd].meta.fa[nd];
		}
		return high->meta.deep < low->meta.deep ? high : low;
	}
};

#undef NODE_C
#undef EDGE_C

#undef ID

