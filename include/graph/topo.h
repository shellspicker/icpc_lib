#define NODE_C typename graph::node
#define EDGE_C typename graph::edge

template<typename graph>
struct topo {
	using node = NODE_C;
	using edge = EDGE_C;

	graph *g;
	node *nd;

	topo(graph *g_) : g(g_), nd(&g->nodes[0]) {}
#if BFS
	pair<bool, vector<int>> sort_bfs() {
#define add(o) \
		if (!o.meta.in) ({ \
			que.push(o.id()); \
		})

		node *v;
		edge *e;
		vector<int> ret;
		queue<int> que;
		fup_range (u, 0, g->size())
			add(u[nd]);
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			u[nd].meta.pos = ret.size();
			ret.push_back(u);
			for (int ei : u[nd].link) {
				tie(v, e) = g->extend(ei);
				v->meta.in--;
				add(v->id()[nd]);
			}
		}
		return {ret.size() == g->size(), ret};
#undef add
	}
#endif

#if DFS
	pair<bool, vector<int>> sort_dfs() {
		vector<int> ret;
		function<bool(node *)> dfs = [&](node *u) -> bool {
			node *v;
			edge *e;
			auto &mt = u->meta;
			mt.flag = -1;
			for (int ei : u->link) {
				tie(v, e) = g->extend(ei);
				if (!~v->meta.flag)
					return 0;
				if (!v->meta.flag && !dfs(v))
					return 0;
			}
			mt.flag = 1;
			ret.push_back(u->id());
			return 1;
		};
		fup_range (i, 0, g->size())
			if (!i[nd].meta.flag)
				dfs(&i[nd]);
		reverse(it_each(ret));
		fup_range (i, 0, ret.size())
			ret[i][nd].meta.pos = i;
		return {ret.size() == g->size(), ret};
	}
};
#endif

#undef NODE_C
#undef EDGE_C

#undef BFS
#undef DFS

