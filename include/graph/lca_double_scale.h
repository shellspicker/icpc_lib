#define NODE_C typename graph::node
#define EDGE_C typename graph::edge

template<typename graph>
struct lca_double_scale {
	using node = NODE_C;
	using edge = EDGE_C;

	graph *g;
	node *nd;
	vector<vector<int>> ac;

	void init(graph *g_, node *root)
	{
		function<void(node *, int, int)> dfs = [&](node *u, int f, int lev) {
			auto &mt = u->meta;
			node *v;
			edge *e;
			mt.deep = lev;
			ac[0][u->id()] = f;
			for (int ei : u->link) {
				tie(v, e) = g->extend(ei);
				if (v->id() == f)
					continue;
				dfs(v, u->id(), lev + 1);
			}
		};
		g = g_;
		nd = g->baseaddr;
		ac.resize(1);
		ac[0].resize(g->size());
		dfs(root, -1, 0);
		double_scale(ac);
	}

	node *query(node *low, node *high)
	{
#define go(x, d) (&ac[d][x->id()][nd])
#define diff (low->meta.deep - high->meta.deep)
		if (diff < 0)
			return query(high, low);
		int xp = ac.size();
		fwn_range (d, 0, xp)
			while ((1 << d) <= diff)
				low = go(low, d);
		if (low == high)
			return low;
		fwn_range (d, 0, xp)
			while (go(low, d) != go(high, d))
				low = go(low, d), high = go(high, d);
		return go(low, 0);
#undef go
#undef diff
	}
};

#undef NODE_C
#undef EDGE_C

