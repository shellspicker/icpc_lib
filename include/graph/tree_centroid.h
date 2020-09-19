#pragma once

#pragma message \
usage_begin("tree_centroid.h") \
line("include:") \
line("\tgraph/graph.h") \
line("synopsis:") \
line("\tnode *tree_centroid(graph *);") \
line("必要信息:") \
line("\tv_info:") \
line("\t\tbool vis;") \
line("\t\tint size, heavy;") \
usage_end()

template<typename graph>
typename graph::node *tree_centroid(graph *g) {
	using node = typename graph::node;
	using edge = typename graph::edge;
	int m2;
	node *ret;
	function<void()> init = [&]() {
		m2 = inf32;
		for (node &nd : g->nodes) {
			nd.meta.vis = 0;
		}
	};
	function<void(node *)> dfs = [&](node *u) {
		auto &meta = u->meta;
		node *v;
		edge *e;
		meta.vis = 1;
		meta.size = 1;
		meta.heavy = -inf32;
		for (int ei : u->link) {
			tie(v, e) = g->extend(ei);
			if (v->meta.vis)
				continue;
			dfs(v);
			meta.size += v->meta.size;
			meta.heavy = max(meta.heavy, v->meta.size);
		}
		meta.heavy = max(meta.heavy, int(g->nodes.size() - meta.size));
		if (meta.heavy < m2) {
			m2 = meta.heavy;
			ret = u;
		}
		meta.vis = 0;
	};
	init();
	dfs(&g->nodes[0]);
	return ret;
}
