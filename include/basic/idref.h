#pragma once

/*
 * 伪离散化.
 */
template <typename T>
class idref {
	int id_cnt;
	map<T, int> mmp;
	map<int, T> orig;
public:
	void init() {
		id_cnt = 0;
		mmp.clear();
		orig.clear();
	}
	int cnt() {
		return id_cnt;
	}
	int get_id(T s)
	{
		if (mmp.count(s))
			return mmp[s];
		int res;
		mmp[s] = res = id_cnt++;
		orig[res] = s;
		return res;
	}
	T get_orig(int id) {
		assert(orig.count(id));
		return orig[id];
	}
};
