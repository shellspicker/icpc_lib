/*
 * dsu, 带路径压缩, link有严格的从属关系.
 */
class dsu {
	vector<int> fa;
public:
	dsu() {}
	dsu(int n) {
		init(n);
	}
	void init(int n) {
		fa.resize(n);
		fup_range (i, 0, n)
			fa[i] = i;
	}
	int set(int x) {
		return fa[x] == x ? x : fa[x] = set(fa[x]);
	}
	template<typename ...var>
	void id(var &&...args) {
		initializer_list<int>{(args = set(args), 0)...};
	}
	bool link(int mas, int slv) {
		id(mas, slv);
		if (mas == slv)
			return 0;
		fa[slv] = mas;
		return 1;
	}
	bool same(int x, int y) {
		id(x, y);
		return x == y;
	}
};

template<class ds, class grp>
void comb_helper(ds &ref, grp &cc, typename ds::node_t *o, int a, int b) {
	ref[a] == o ? cc.link(a, b) : cc.link(b, a);
}

