/*
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
*/

/*
 * node.meta:
 *   int dist, pre;
 */
template<typename graph>
struct diameter {
	using node = typename graph::node;
	using edge = typename graph::edge;
	graph &g;
	node *nd;
public:
	diameter(graph &_1) : g(_1), nd(&g[0]) {}
	tuple<int, vector<int>> run(int source, bool print) {
		int diameter;
		vector<int> path;
		auto bfs = [&](int st, bool perm) {
			int m2, id;
			queue<int> que;
			node *v;
			edge *e;
			fup_range (u, 0, g.size())
				g[u].meta.dist = inf32;
			que.push(st);
			g[st].meta.dist = 0;
			g[st].meta.pre = -1;
			m2 = -inf32;
			while (!que.empty()) {
				int u = que.front(); que.pop();
				if (m2 < g[u].meta.dist)
					m2 = g[id = u].meta.dist;
				for (int ei : g[u].link) {
					tie(v, e) = g.extend(ei);
					if (g[u].meta.dist + 1 < v->meta.dist) {
						v->meta.pre = u;
						v->meta.dist = g[u].meta.dist + 1;
						que.push(v->id());
					}
				}
			}
			diameter = m2;
			source = id;
			if (perm) {
				int cur = id;
				while (cur ^ -1) {
					path.push_back(cur);
					cur = g[cur].meta.pre;
				}
			}
		};
		bfs(source, 0);
		bfs(source, print);
		return tie(diameter, path);
	}
};

