#ifndef BIT_H
#define BIT_H 1

/*
 * 注意, 下标起始1, 0是没有数据的.
 */
template<typename tp>
class bit {
	vector<tp> ds;
public:
	void resize(int len) { ds.resize(len); }
	void clear() { fill(ds.begin(), ds.end(), 0); }
	void add(int x, int v) {
		assert(0 < x); // notice.
		while (x < ds.size()) {
			ds[x] += v;
			x += cto(x);
		}
	}
	tp presum(int x) {
		if (x < 0)
			return 0;
		tp ans = 0;
		while (x) {
			ans += ds[x];
			x -= cto(x);
		}
		return ans;
	}
	tp sufsum(int x) {
		return presum(ds.size() - 1) - presum(x - 1);
	}
	tp presum_range(int l, int r) {
		return presum(r) - presum(l - 1);
	}
	int rank(int x) {
		return presum(x - 1) + 1;
	}
	int kth(int k) {
		int x, lo, hi, mid;
		lo = 1, hi = ds.size() - 1;
		while (lo <= hi) {
			mid = midpoint(lo, hi);
			if (k <= presum(mid))
				hi = mid - 1;
			else
				lo = mid + 1;
		}
		x = k <= presum(lo) ? lo : 0;
		return x;
	}
};

#endif
