#pragma once

#pragma message \
usage_begin("lca_tarjan.h") \
line("include:") \
line("\tgraph/graph.h") \
line("\tdata_structure/dsu.h") \
line("synopsis:") \
line("\tvoid lca_tarjan(graph *, int);") \
line("必要信息:") \
line("\tv_info:") \
line("\t\tbool vis;") \
line("\t\tvector<pair<int, int *>>lca_query;") \
line("tip:") \
line("\tdsu不带rank优化.") \
usage_end()

template<typename graph>
void lca_tarjan(graph *g, int root) {
	using node = typename graph::node;
	using edge = typename graph::edge;
	dsu group;
	function<void()> init = [&]() {
		group.init(g->nodes.size());
		for (auto &nd : g->nodes)
			nd.meta.vis = 0;
	};
	function<void(node *)> dfs = [&](node *u) {
		auto &meta = u->meta;
		node *v;
		meta.vis = 1;
		for (int ei : u->link) {
			tie(v, ignore) = g->extend(ei);
			if (v->meta.vis)
				continue;
			dfs(v);
			group.link(u->id, v->id);
		}
		for (auto qa : u->meta.lca_query) {
			node *v = &g->nodes[qa.first];
			if (v->meta.vis)
				*qa.second = group.set(v->id);
		}
		u->meta.lca_query.clear();
	};
	init();
	dfs(&g->nodes[root]);
}
