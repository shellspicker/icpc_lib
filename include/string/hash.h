#pragma once

/*
 * normal hash.
 */
template<typename tp>
void combine(size_t &seed, const tp &x)
{
	seed ^= hash<tp>()(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
template<typename tp>
size_t hash_val(vector<tp> &&vec)
{
	size_t seed = 0;
	for (auto x : vec)
		combine(seed, x);
	return seed;
}
template<typename ...var>
size_t hash_val(var &&...args)
{
	size_t seed = 0;
	initializer_list<int>{(combine(seed, forward<var>(args)), 0)...};
	return seed;
}
/*
 * bkdr hash.
 */
class precalc_hash {
	ull seed;
	vector<ull> exp, hval;

public:
	precalc_hash(ull s) : seed(s) {}

	precalc_hash(ull s, size_t len) : precalc_hash(s) {
		exp.resize(len);
		exp[0] = 1;
		fup_range (i, 1, len - 1)
			exp[i] = exp[i - 1] * seed;
	}

	template<typename iter>
	ull once(iter l, size_t len) {
		ull ret = 0;
		fup_range (i, 0, len)
			ret = ret * seed + (*l++);
		return ret;
	}

	template<typename iter>
	void add(iter l, size_t len, size_t st = 0) {
		hval.resize(st + len);
		fup_range (i, 0, len)
			hval[st + i] = special(0llu, hval, st + i - 1) * seed + (*l++);
	}

	ull get(size_t l, size_t len) {
		return hval[ltor(l, len)] - special(0llu, hval, l - 1) * exp[len];
	}

	pair<int, bool> lcs(int p1, int p2, int dir) {
		if (p1 == p2)
			return {p1, 1};
		struct table {
			int limit;
		} tbl[2];
		tbl[0] = {min(p1, p2) + 1};
		tbl[1] = {hval.size() - max(p1, p2)};
		int idx = (dir + 1) / 2;
		int lef = 0, rig = tbl[idx].limit, m2l = rig;
		bool cmp;
		while (lef <= rig) {
			int mid = midpoint(lef, rig);
			struct start {
				int p1, p2;
			} st[2];
			st[0] = {rtol(p1, mid), rtol(p2, mid)};
			st[1] = {p1, p2};
			if (get(st[idx].p1, mid) == get(st[idx].p2, mid))
				lef = mid + 1;
			else
				rig = mid - 1;
		}
		if (rig == m2l)
			cmp = 0 < (p1 - p2) * dir;
		else
			cmp = get(p1 + dir * rig, 1) < get(p2 + dir * rig, 1);
		return {rig, cmp};
	}
};
