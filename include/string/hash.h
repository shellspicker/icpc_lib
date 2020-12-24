/*
 * normal hash.
 */
ull self_hash(const string &s)
{
	ull ret = 0;
	for (auto c : s)
		ret = ret * 3137 + c;
	return ret;
}
template<typename tp>
ull self_hash(const vector<tp> &v)
{
	ull ret = 0;
	for (auto x : v)
		ret = ret * 3137 + x;
	return ret;
}
template<typename tp>
ull self_hash(const tp &x)
{
	return hash<tp>()(x);
}
template<typename tp>
void combine(ull &seed, const tp &x)
{
	seed ^= hash<tp>()(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
template<typename tp>
ull hash_val(const vector<tp> &vec)
{
	ull ret = 0;
	for (auto x : vec)
		combine(ret, x);
	return ret;
}
template<typename tp>
ull hash_val(vector<tp> &&vec)
{
	ull ret = 0;
	for (auto x : vec)
		combine(ret, x);
	return ret;
}
template<typename ...var>
ull hash_val(var &&...args)
{
	ull ret = 0;
	initializer_list<int>{(combine(ret, forward<var>(args)), 0)...};
	return ret;
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

