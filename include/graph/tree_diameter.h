#pragma once

#define NODE_C typename graph::node
#define EDGE_C typename graph::edge

template<typename graph>
int tree_diameter(graph *g, NODE_C *root) {
	using node = NODE_C;
	using edge = EDGE_C;

	int ret;
	function<void()> init = [&]() {
		ret = 0;
		for (node &nd : g->nodes)
			nd.meta.vis = 0;
	};
	function<void(node *)> dfs = [&](node *u) {
		auto &mt = u->meta;
		node *v;
		edge *e;
		mt.vis = 1;
		mt.chain = 0;
		for (int ei : u->link) {
			tie(v, e) = g->extend(ei);
			if (v->meta.vis)
				continue;
			dfs(v);
			int chain = v->meta.chain + e->meta.dist;
			ret = max(ret, mt.chain + chain);
			mt.chain = max(mt.chain, chain);
		}
		mt.vis = 0;
	};

	init();
	dfs(root);
	return ret;
}

#undef NODE_C
#undef EDGE_C
