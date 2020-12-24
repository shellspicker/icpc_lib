class dsu {
	vector<int> fa;
#if RANK
	vector<int> lev;
#endif
public:
	void init(int n) {
		fa.resize(n);
#if RANK
		lev.resize(n);
#endif
		fup_range (i, 0, n) {
			fa[i] = i;
#if RANK
			lev[i] = 0;
#endif
		}
	}
	int set(int x) {
		return fa[x] == x ? x : fa[x] = set(fa[x]);
	}
	bool link(int master, int slave) {
		int x = set(master), y = set(slave);
		if (x == y)
			return 0;
#if RANK
		if (lev[x] < lev[y])
			fa[x] = fa[y];
		else
			fa[y] = fa[x];
		if (lev[x] == lev[y])
			lev[x]++;
#else
		fa[y] = x;
#endif
		return 1;
	}
	bool same(int x, int y) {
		return set(x) == set(y);
	}
};

