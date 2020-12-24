#define NODE_C typename graph::node
#define EDGE_C typename graph::edge

template<typename graph>
NODE_C *tree_centroid(graph *g, NODE_C *root) {
	using node = NODE_C;
	using edge = EDGE_C;

	int m2;
	node *ret;
	function<void()> init = [&]() {
		m2 = inf32;
		for (node &nd : g->nodes) {
			nd.meta.vis = 0;
		}
	};
	function<void(node *)> dfs = [&](node *u) {
		auto &mt = u->meta;
		node *v;
		edge *e;
		mt.vis = 1;
		mt.size = 1;
		mt.heavy = -inf32;
		for (int ei : u->link) {
			tie(v, e) = g->extend(ei);
			if (v->meta.vis)
				continue;
			dfs(v);
			mt.size += v->meta.size;
			mt.heavy = max(mt.heavy, v->meta.size);
		}
		mt.heavy = max(mt.heavy, int(g->size() - mt.size));
		if (mt.heavy < m2) {
			m2 = mt.heavy;
			ret = u;
		}
		mt.vis = 0;
	};

	init();
	dfs(root);
	return ret;
}

#undef NODE_C
#undef EDGE_C

