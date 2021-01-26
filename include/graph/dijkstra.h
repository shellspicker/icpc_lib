/*
 * node.meta:
 *   bool vis;
 *   dtp dist;
 *
 * edge.meta:
 *   dtp cost;
 */
template<typename graph>
struct dijkstra {
	using node = typename graph::node_t;
	using edge = typename graph::edge_t;
	graph &g;
	node *nd;
	dijkstra(graph &_1) : g(_1), nd(g.node_base) {}
	template<typename dtp>
	void get(int source) {
		node *v;
		edge *e;
		fup_range (i, 0, g.size()) {
			auto &mt = nd[i].meta;
			mt.vis = 0;
			mt.dist = get_inf<dtp>();
		}
		struct hnode {
			int x;
			dtp d;
			hnode(int _1, dtp _2) : x(_1), d(_2) {}
			bool operator <(const hnode &r) const {
				return d > r.d;
			}
		};
		priority_queue<hnode> que;
		que.push({source, nd[source].meta.dist = 0});
		while (!que.empty()) {
			auto now = que.top();
			que.pop();
			int u = now.x;
			auto &mt = nd[u].meta;
			if (mt.vis)
				continue;
			mt.vis = 1;
			for (int ei : g[u].link) {
				tie(v, e) = g.extend(ei);
				if (now.d + e->meta.cost < nd[v->id()].meta.dist) {
					nd[v->id()].meta.dist = now.d + e->meta.cost;
					que.push({v->id(), nd[v->id()].meta.dist});
				}
			}
		}
	}
};

