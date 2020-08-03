#ifndef DSU_H
#define DSU_H 1

class dsu {
	vector<int> fa, lev;
public:
	void init(int n) {
		fa.resize(n);
		lev.resize(n);
		fup_range (i, 0, n)
			fa[i] = i, lev[i] = 0;
	}
	int set(int x) {
		return fa[x] == x ? x : fa[x] = set(fa[x]);
	}
	bool link(int x, int y) {
		x = set(x), y = set(y);
		if (x == y)
			return 0;
		if (lev[x] < lev[y])
			fa[x] = fa[y];
		else
			fa[y] = fa[x];
		if (lev[x] == lev[y])
			lev[x]++;
		return 1;
	}
	bool same(int x, int y) {
		return set(x) == set(y);
	}
};

#endif
