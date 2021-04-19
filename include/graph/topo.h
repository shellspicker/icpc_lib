/*
 * bfs
 *
 * macro:
 *   BFS
 *
 * node.meta:
 *   int in(0), pos;
 */
#if BFS
template<typename graph>
class topo_bfs {
	using node = typename graph::node;
	using edge = typename graph::edge;
	graph &g;
	node *nd;
public:
	topo_bfs(graph &_1) : g(_1), nd(g.node_base) {}
	pair<bool, vector<int>> get() {
#define add(o) \
		if (!o.meta.in) ({ \
			que.push(o.id()); \
		})
		node *v;
		edge *e;
		vector<int> ret;
		queue<int> que;
		fup_range (u, 0, g.size())
			add(g[u]);
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			g[u].meta.pos = ret.size();
			ret.push_back(u);
			for (int ei : g[u].link) {
				tie(v, e) = g.extend(ei);
				v->meta.in--;
				add(g[v->id()]);
			}
		}
		return {ret.size() == g.size(), ret};
#undef add
	}
};
#endif

/*
 * dfs
 *
 * macro:
 *   DFS
 *
 * node.meta:
 *   int flag(0), pos;
 */
#if DFS
template<typename graph>
class topo_dfs {
	using node = typename graph::node;
	using edge = typename graph::edge;
	graph &g;
	node *nd;
public:
	topo_dfs(graph &_1) : g(_1), nd(g.node_base) {}
	pair<bool, vector<int>> get() {
		vector<int> ret;
		function<bool(int)> dfs = [&](int u) -> bool {
			node *v;
			edge *e;
			auto &mt = g[u].meta;
			mt.flag = -1;
			for (int ei : g[u].link) {
				tie(v, e) = g.extend(ei);
				if (!~v->meta.flag)
					return 0;
				if (!v->meta.flag && !dfs(v->id()))
					return 0;
			}
			mt.flag = 1;
			ret.push_back(u);
			return 1;
		};
		fup_range (u, 0, g.size())
			if (!g[u].meta.flag)
				dfs(u);
		reverse(it_each(ret));
		fup_range (i, 0, ret.size())
			g[ret[i]].meta.pos = i;
		return {ret.size() == g.size(), ret};
	}
};
#endif

#undef BFS
#undef DFS

