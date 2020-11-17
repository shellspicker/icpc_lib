#pragma once

#define NODE_C typename graph::node
#define EDGE_C typename graph::edge

template<typename graph>
struct bellman_ford {
	using node = NODE_C;
	using edge = EDGE_C;

	graph *g;
	node *nd;

	bellman_ford(graph *_1) : g(_1), nd(&g->nodes[0]) {}

	template<typename dtp>
	tuple<bool, vector<dtp>> get(int ss) {
		vector<bool> inq(g->size(), 0);
		vector<int> cnt(g->size(), 0);
		bool negative = 0;
		vector<dtp> dist(g->size(), get_inf<dtp>());
		node *v;
		edge *e;
		queue<int> que;
		dist[ss] = 0;
		que.push(ss);
		while (!que.empty()) {
			int u = que.front(); que.pop();
			inq[u] = 0;
			for (int ei : g->nodes[u].link) {
				tie(v, e) = g->extend(ei);
				if (dist[u] + e->meta.cost < dist[v->id()]) {
					dist[v->id()] = dist[u] + e->meta.cost;
					if (!inq[v->id()]) {
						inq[v->id()] = 1;
						que.push(v->id());
						if (++cnt[v->id()] == g->size()) {
							negative = 1;
							goto end;
						}
					}
				}
			}
		}
end:
		return make_tuple(negative, dist);
	}
};
