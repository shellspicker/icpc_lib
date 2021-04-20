/*
 * include
 *   graph/graph_reverse.h
 * node.meta
 *   bool vis;
 *   int gid;
 */
template<typename graph>
class scc_kosaraju {
	graph &g;
	using node = typename graph::node;
	using edge = typename graph::edge;
public:
	scc_kosaraju(graph &_1) : g(_1) {}
	tuple<vector<vector<int>>, graph> run() {
		vector<vector<int>> scc_group;
		graph g_shrink;
		graph g_rev;
		vector<int> seq;
		function<void(int)> dfs_origin = [&](int u) {
			auto &mt = g[u].meta;
			node *v;
			edge *e;
			if (mt.vis)
				return;
			mt.vis = 1;
			for (int ei : g[u].link) {
				tie(v, e) = g.extend(ei);
				dfs_origin(v->id());
			}
			seq.push_back(u);
		};
		function<void(int)> dfs_rev = [&](int u) {
			auto &mt = g_rev[u].meta;
			node *v;
			edge *e;
			if (mt.gid ^ -1)
				return;
			mt.gid = scc_group.size() - 1;
			scc_group.back().push_back(u);
			for (int ei : g_rev[u].link) {
				tie(v, e) = g_rev.extend(ei);
				dfs_rev(v->id());
			}
		};
		auto shrink = [&]() {
			g_shrink.resize(scc_group.size());
			fup_range (i, 0, g.edges.size()) {
				auto &e = g.edges[i];
				int id[2] = {g[e.from].meta.gid, g[e.to].meta.gid};
				if (id[0] ^ id[1])
					g_shrink.add(id[0], id[1]);
			}
			fup_range (u, 0, g_shrink.size()) {
				sort(it_each(g_shrink[u].link));
				g_shrink[u].link.erase(unique(it_each(g_shrink[u].link)), g_shrink[u].link.end());
			}
		};
		auto scan = [&]() {
			graph_reverse<graph> rev(g);
			g_rev = rev.get();
			fup_range (u, 0, g.size()) {
				g[u].meta.vis = 0;
				g_rev[u].meta.gid = -1;
			}
			fup_range (u, 0, g.size())
				dfs_origin(u);
			fwn_range (i, 0, seq.size()) {
				int u = seq[i];
				auto &mt = g_rev[u].meta;
				if (mt.gid == -1) {
					scc_group.push_back(vector<int>());
					dfs_rev(u);
				}
			}
			fup_range (u, 0, g.size())
				g[u].meta.gid = g_rev[u].meta.gid;
		};
		scan();
		shrink();
		return {scc_group, g_shrink};
	}
};

