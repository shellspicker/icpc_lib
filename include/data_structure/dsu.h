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
	bool link(int master, int slave) {
		int x = set(master), y = set(slave);
		if (x == y)
			return 0;
		fa[y] = x;
		return 1;
	}
	bool same(int x, int y) {
		return set(x) == set(y);
	}
};

