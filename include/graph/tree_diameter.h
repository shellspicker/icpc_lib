#pragma once

#pragma message \
usage_begin("tree_diameter.h") \
line("include:") \
line("\t\"graph/graph.h\"") \
line("synopsis:") \
line("\tint tree_diameter(graph *);") \
line("必要信息:") \
line("\tv_info:") \
line("\t\tbool vis;") \
line("\t\tint chain;") \
line("\te_info:") \
line("\t\tint dist;") \
usage_end()

template<typename graph>
int tree_diameter(graph *g) {
	using node = typename graph::node;
	using edge = typename graph::edge;
	int ret;
	function<void()> init = [&]() {
		ret = 0;
		for (node &nd : g->nodes)
			nd.meta.vis = 0;
	};
	function<void(node *)> dfs = [&](node *u) {
		auto &meta = u->meta;
		node *v;
		edge *e;
		meta.vis = 1;
		meta.chain = 0;
		for (int ei : u->link) {
			tie(v, e) = g->extend(ei);
			if (v->meta.vis)
				continue;
			dfs(v);
			int chain = v->meta.chain + e->meta.dist;
			ret = max(ret, meta.chain + chain);
			meta.chain = max(meta.chain, chain);
		}
		meta.vis = 0;
	};
	init();
	dfs(&g->nodes[0]);
	return ret;
}