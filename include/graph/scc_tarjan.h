/*
 * node.meta
 *   int tin, gid;
 */
template<typename graph>
class scc_tarjan {
	graph &g;
	using node = typename graph::node;
	using edge = typename graph::edge;
public:
	scc_tarjan(graph &_1) : g(_1) {}
	tuple<vector<vector<int>>, graph> run() {
		int clk;
		stack<int> st;
		vector<vector<int>> scc_group;
		graph g_shrink;
		function<int(int)> dfs = [&](int u) {
			int low_now = g[u].meta.tin = ++clk;
			st.push(u);
			node *v;
			edge *e;
			for (int ei : g[u].link) {
				tie(v, e) = g.extend(ei);
				if (!g[v->id()].meta.tin) {
					int low_nxt = dfs(v->id());
					low_now = min(low_now, low_nxt);
				} else if (g[v->id()].meta.gid == -1) {
					low_now = min(low_now, g[v->id()].meta.tin);
				}
			}
			if (low_now == g[u].meta.tin) {
				int x;
				scc_group.push_back(vector<int>());
				x = -1;
				do {
					x = st.top();
					st.pop();
					g[x].meta.gid = scc_group.size() - 1;
					scc_group.back().push_back(x);
				} while (x ^ u);
			}
			return low_now;
		};
		auto scan = [&]() {
			clk = 0;
			fup_range (u, 0, g.size()) {
				auto &mt = g[u].meta;
				mt.tin = 0;
				mt.gid = -1;
			}
			fup_range (u, 0, g.size())
				if (!g[u].meta.tin)
					dfs(u);
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
		scan();
		shrink();
		return {scc_group, g_shrink};
	};
};
