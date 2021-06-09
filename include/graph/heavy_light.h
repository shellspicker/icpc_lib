/*
 * node.meta:
 *   int size, heavy, deep, fa, ac;
 */
template<typename graph>
struct heavy_light {
	using node = typename graph::node;
	using edge = typename graph::edge;

	graph &g;
	node *nd;
#if ID
	vector<int> id, ref;
#endif

	heavy_light(graph &_1) :
		g(_1), nd(&g.nodes[0]) {}

	void init(int root) {
#if ID
		int clk;
#endif
		function<void(int, int, int)> dfs = [&](int u, int f, int lev) {
			node *v;
			edge *e;
			auto &mt = g[u].meta;
			mt.size = 1;
			mt.heavy = -1;
			mt.deep = lev;
			mt.fa = f;
			for (int ei : g[u].link) {
				tie(v, e) = g.extend(ei);
				if (v->id() == f)
					continue;
				dfs(v->id(), u, lev + 1);
				mt.size += v->meta.size;
				if (!~mt.heavy || g[mt.heavy].meta.size < v->meta.size)
					mt.heavy = v->id();
			}
		};
		function<void(int, int)> make = [&](int u, int chain) {
			node *v;
			edge *e;
			auto &mt = g[u].meta;
			mt.ac = chain;
#if ID
			ref[id[g[u].id()] = clk++] = g[u].id();
#endif
			if (!~mt.heavy)
				return;
			make(mt.heavy, chain);
			for (int ei : g[u].link) {
				tie(v, e) = g.extend(ei);
				if (v->id() == mt.fa || v->id() == mt.heavy)
					continue;
				make(v->id(), v->id());
			}
		};
		function<void()> get_id = [&]() {
#if ID
			clk = 0;
			id.resize(g.size());
			ref.resize(g.size());
#endif
			make(root, g[root].id());
		};
		dfs(root, -1, 0);
		get_id();
	}

	int lca(int low, int high) {
#define check(lo, hi) (!(g[hi].meta.deep < g[lo].meta.deep))
		while (g[low].meta.ac != g[high].meta.ac) {
			if (check(g[low].meta.ac, g[high].meta.ac))
				swap(low, high);
			low = g[g[low].meta.ac].meta.fa;
		}
		if (check(low, high))
			swap(low, high);
		return high;
#undef check
	}

	vector<pair<int, int>> lca_node(int low, int high) {
#define check(lo, hi) (!(g[hi].meta.deep < g[lo].meta.deep))
		vector<pair<int, int>> ret;
		while (g[low].meta.ac != g[high].meta.ac) {
			if (check(g[low].meta.ac, g[high].meta.ac))
				swap(low, high);
			ret.push_back({id[low[nd].meta.ac], id[low]});
			low = g[g[low].meta.ac].meta.fa;
		}
		if (check(low, high))
			swap(low, high);
		ret.push_back({id[high], id[low]});
		return ret;
#undef check
	}

	vector<pair<int, int>> lca_edge(int low, int high) {
#define check(lo, hi) (!(g[hi].meta.deep < g[lo].meta.deep))
		vector<pair<int, int>> ret;
		while (g[low].meta.ac != g[high].meta.ac) {
			if (check(g[low].meta.ac, g[high].meta.ac))
				swap(low, high);
			ret.push_back({id[low[nd].meta.ac], id[low]});
			low = g[g[low].meta.ac].meta.fa;
		}
		if (check(low, high))
			swap(low, high);
		if (low ^ high)
			ret.push_back({id[high] + 1, id[low]});
		return ret;
#undef check
	}
};

#undef ID

