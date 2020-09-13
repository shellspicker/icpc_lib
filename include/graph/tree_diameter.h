#pragma once

#pragma message \
usage_begin("tree_diameter.h") \
line("前置:") \
line("\t\"graph/graph.h\"") \
line("v_info必要信息:") \
line("\tint chain;") \
line("\tbool vis;") \
line("e_info必要信息:") \
line("\tint cost;") \
usage_end()

template<typename graph>
int tree_diameter(graph *g) {
	using node = typename graph::node;
	using edge = typename graph::edge;
	int ret;
	function<void()> init = [&]() {
		ret = 0;
		for (node &nd : g->nodes)
			nd.info.vis = 0;
	};
	function<void(node &)> dfs = [&](node &u) {
		u.info.vis = 1;
		u.info.chain = 0;
		for (int ei : u.eid) {
			edge &e = g->edges[ei];
			node &v = g->nodes[e.to];
			if (v.info.vis)
				continue;
			dfs(v);
			int chain = v.info.chain + e.info.cost;
			ret = max(ret, u.info.chain + chain);
			u.info.chain = max(u.info.chain, chain);
		}
	};
	init();
	dfs(g->nodes[0]);
	return ret;
}
