#ifndef GRAPH_H
#define GRAPH_H 1

template <typename tp>
class graph {
public:
	struct edge {
		int from, to;
		tp cost;
	};
	vector<edge> edges;
	vector<vector<int>> g;
	int n;
	graph(int vn = 0) : n(vn) {
		clear();
		g.resize(vn);
	}
	void clear() {
		edges.clear();
		for (auto &v : g)
			v.clear();
		g.clear();
	}
	virtual int add(int from, int to, tp cost) = 0;
};
template <typename tp>
class digraph : public graph<tp> {
public:
	using typename graph<tp>::edge;
	using graph<tp>::edges;
	using graph<tp>::g;
	using graph<tp>::n;
	digraph(int vn = 0) : graph<tp>(vn) {}
	void resize(int vn) {
		new (this) digraph(vn);
	}
	vector<int> &operator [](int u) {
		return g[u];
	}
	edge &info(int i) {
		return edges[i];
	}
	int add(int from, int to, tp cost = 1) {
		assert(inrange(from, range(0, n)) && inrange(to, range(0, n)));
		edges.push_back({from, to, cost});
		int id = (int)edges.size();
		g[from].push_back(id - 1);
		return id;
	}
	digraph<tp> reverse() const {
		digraph<tp> rev(n);
		for (auto &e : edges)
			rev.add(e.to, e.from, e.cost);
		return rev;
	}
};
template <typename tp>
class undigraph : public graph<tp> {
public:
	using typename graph<tp>::edge;
	using graph<tp>::edges;
	using graph<tp>::g;
	using graph<tp>::n;
	undigraph(int vn = 0) : graph<tp>(vn) {}
	void resize(int vn) {
		new (this) undigraph(vn);
	}
	vector<int> &operator [](int u) {
		return g[u];
	}
	edge &info(int i) {
		return edges[i];
	}
	int add(int from, int to, tp cost = 1) {
		assert(inrange(from, range(0, n)) && inrange(to, range(0, n)));
		edges.push_back({from, to, cost});
		edges.push_back({to, from, cost});
		int id = (int)edges.size();
		g[from].push_back(id - 2);
		g[to].push_back(id - 1);
		return id;
	}
};

#endif
