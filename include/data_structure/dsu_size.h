/*
 * dsu, 带集合大小, 启发式合并.
 */
class dsu {
	vector<int> e;
public:
	dsu() {}
	dsu(int n) {
		init(n);
	}
	void init(int n) {
		e.assign(n, -1);
	}
	int size(int x) {
		return -e[set(x)];
	}
	int set(int x) {
		return e[x] < 0 ? x : set(e[x]);
	}
	bool link(int x, int y) {
		x = set(x), y = set(y);
		if (x == y)
			return 0;
		if (!(e[x] < e[y]))
			swap(x, y);
		e[x] += e[y];
		e[y] = x;
		return 1;
	}
	bool same(int x, int y) {
		return set(x) == set(y);
	}
};

