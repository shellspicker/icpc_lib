#define NODE_C typename graph::node
#define EDGE_C typename graph::edge

template<typename graph>
void lca_tarjan(graph *g, NODE_C *root) {
	using node = NODE_C;
	using edge = EDGE_C;

	node *nd = g->baseaddr;
	dsu group;
	function<void()> init = [&]() {
		group.init(g->size());
		for (auto &nd : g->nodes)
			nd.meta.vis = 0;
	};
	function<void(node *)> dfs = [&](node *u) {
		auto &mt = u->meta;
		node *v;
		edge *e;
		mt.vis = 1;
		for (int ei : u->link) {
			tie(v, e) = g->extend(ei);
			if (v->meta.vis)
				continue;
			dfs(v);
			group.link(u->id(), v->id());
		}
		for (auto qa : mt.lca_query) {
			node *v = &qa.first[nd];
			if (v->meta.vis)
				*qa.second = group.set(v->id());
		}
		mt.lca_query.clear();
	};

	init();
	dfs(root);
}

#undef NODE_C
#undef EDGE_C

