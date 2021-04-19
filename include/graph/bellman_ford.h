/*
 * node.meta:
 *   bool inq;
 *   int cnt;
 *   dtp dist;
 *
 * edge.meta:
 *   dtp cost;
 */
template<typename graph>
struct bellman_ford {
	using node = typename graph::node;
	using edge = typename graph::edge;
	graph &g;
	node *nd;
	bellman_ford(graph &_1) : g(_1), nd(g.node_base) {}
	template<typename dtp>
	bool get(int source) {
		node *v;
		edge *e;
		fup_range (i, 0, g.size()) {
			auto &mt = nd[i].meta;
			mt.inq = 0;
			mt.cnt = 0;
			mt.dist = get_inf<dtp>();
		}
		bool negative = 0;
		queue<int> que;
		nd[source].meta.dist = 0;
		que.push(source);
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			auto &mt = nd[u].meta;
			mt.inq = 0;
			for (int ei : g[u].link) {
				tie(v, e) = g.extend(ei);
				if (mt.dist + e->meta.cost < nd[v->id()].meta.dist) {
					nd[v->id()].meta.dist = mt.dist + e->meta.cost;
					if (!nd[v->id()].meta.inq) {
						nd[v->id()].meta.inq = 1;
						que.push(v->id());
						if (++nd[v->id()].meta.cnt == g.size()) {
							negative = 1;
							goto end;
						}
					}
				}
			}
		}
end:
		return negative;
	}
};

