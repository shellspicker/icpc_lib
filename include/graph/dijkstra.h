#define NODE_C typename graph::node
#define EDGE_C typename graph::edge

template<typename graph>
struct dijkstra {
	using node = NODE_C;
	using edge = EDGE_C;

	graph *g;
	node *nd;

	dijkstra(graph *_1) : g(_1), nd(&g->nodes[0]) {}

	template<typename dtp>
	vector<dtp> get(int ss) {
		vector<bool> done(g->size(), 0);
		vector<dtp> dist(g->size(), get_inf<dtp>());
		node *v;
		edge *e;
		struct hnode {
			int i;
			dtp d;
			hnode(int _1, dtp _2) : i(_1), d(_2) {}
			bool operator <(const hnode &rhs) const {
				return d > rhs.d;
			}
		};
		priority_queue<hnode> que;
		que.push({ss, dist[ss] = 0});
		while (!que.empty()) {
			auto now = que.top(); que.pop();
			int u = now.i;
			if (done[u])
				continue;
			done[u] = 1;
			for (int ei : g->nodes[u].link) {
				tie(v, e) = g->extend(ei);
				if (dist[u] + e->meta.cost < dist[v->id()]) {
					dist[v->id()] = dist[u] + e->meta.cost;
					que.push({v->id(), dist[v->id()]});
				}
			}
		}
		return dist;
	}
};

