#define PERMUTATAION_T template<size_t _1>
#define PERMUTATAION_C permutation<_1>

template<size_t dn>
class permutation {
public:
	static void init() {
		iota(origin, origin + dn, 0);
	}
	permutation() {
		iota(mat, mat + dn, 0);
		ghs();
	}
	permutation(const vector<int> &p) { assign(p); }
	permutation(const vector<int> &pre, const vector<int> &nxt) { assign(pre, nxt); }
	void assign(const vector<int> &p) {
		assert(is_permutation(origin, origin + dn, p.begin()));
		copy(p.begin(), p.end(), mat);
		ghs();
	}
	void assign(const vector<int> &pre, const vector<int> &nxt) {
		auto fn = [](int x) { return inrange(x, 0, int(dn - 1)); };
		assert(find_if_not(pre.begin(), pre.end(), fn) == pre.end());
		assert(find_if_not(nxt.begin(), nxt.end(), fn) == nxt.end());
		assert(is_permutation(pre.begin(), pre.end(), nxt.begin()));
		permutation();
		fup_range (i, 0, pre.size())
			mat[pre[i]] = nxt[i];
		ghs();
	}
	void compos(permutation<dn> &rhs, int tp) {
		int cp[dn];
		memcpy(cp, mat, dn * 4);
		if (!tp)
			fup_range (i, 0, dn)
				mat[i] = cp[rhs.mat[i]];
		else
			fup_range (i, 0, dn)
				mat[rhs.mat[i]] = cp[i];
		ghs();
	}
	permutation<dn> inv() {
		vector<int> v(dn);
		fup_range (i, 0, dn)
			v[mat[i]] = i;
		permutation<dn> ret;
		ret.assign(v);
		return ret;
	}
	tuple<vector<vector<int>>, int> cycle() {
		tuple<vector<vector<int>>, int> ret;
		vector<bool> vis(dn, 0);
		vector<vector<int>> &cycle = get<0>(ret);
		int &period = get<1>(ret);
		period = 1;
		fup_range (x, 0, dn) {
			if (!vis[x]) {
				int nx = x;
				cycle.push_back(vector<int>());
				cycle.back().clear();
				while (!vis[nx]) {
					vis[nx] = 1;
					cycle.back().push_back(nx);
					nx = mat[nx];
				};
				period = lcm(period, int(cycle.back().size()));
			}
		}
		return ret;
	}
	int diff() {
		int ret = 0;
		fup_range (i, 0, dn) if (origin[i] ^ mat[i])
			ret++;
		return ret;
	}
	int diff(permutation<dn> &rhs) {
		int ret = 0;
		fup_range (i, 0, dn) if (mat[i] ^ rhs.mat[i])
			ret++;
		return ret;
	}
	void debug() {
		assert(is_permutation(origin, origin + dn, mat));
		permutation v = inv();
		fio.msg("status:\n");
		fio.msg("plus:  %020llu %02d: ", hs, diff());
		fup_range (i, 0, dn)
			fio.msg("%02d%c", mat[i], " \n"[i == dn - 1]);
		fio.msg("minus: %020llu %02d: ", v.hs, v.diff());
		fup_range (i, 0, dn)
			fio.msg("%02d%c", v.mat[i], " \n"[i == dn - 1]);
		/*
		fio.msg("status, cycle: %d, period: %d\n", cycn, period);
		fup_range (d, 0, 2) {
			fio.msg("%020llu %02d: ", hs[0], diff(0));
			fup_range (i, 0, dn)
				fio.msg("%02d%c", mat[d][i], " \n"[i == dn - 1]);
		}
		*/
	}
	int mat[dn];
	ull hs;
private:
	void ghs() {
		hs = self_hash(vector<int>(mat, mat + dn));
	}
	static int origin[dn];
};
PERMUTATAION_T
int PERMUTATAION_C::origin[_1];

#undef PERMUTATAION_T
#undef PERMUTATAION_C

#define CUBE_T template<class _1>
#define CUBE_C cube<_1>

template<class pm>
class cube
{
public:
	using vpm = vector<pm>;
	static void init() {
		pm::init();
		origin = pm();
	}
	static void level_bfs(vpm &comb, vpm &misc, int limit) {
		queue<pm> que;
		unordered_set<ull> st;
		que.push(origin);
		st.insert(origin.hs);
		comb.push_back(origin);
		auto expand = [&]() {
			int cc = que.size();
			while (!que.empty() && cc--) {
				pm x = que.front(); que.pop();
				for (auto &y : misc) {
					x.compos(y, 0);
					if (!st.count(x.hs)) {
						que.push(x);
						st.insert(x.hs);
						comb.push_back(x);
					}
					x.compos(y, 1);
				}
			}
		};
		fup (lev, 1, limit) {
			if (que.empty())
				break;
			expand();
		}
	}
	static void face_seq(vpm &comb, vpm &body, vpm &face) {
		pm once = origin;
		unordered_set<ull> st;
		auto add = [&]() -> bool {
			bool fd = 0;
			for (auto &x : body) {
				once.compos(x, 0);
				fd |= st.count(once.hs);
				once.compos(x, 1);
				if (fd)
					break;
			}
			if (fd)
				return 0;
			for (auto &x : body) {
				once.compos(x, 0);
				st.insert(once.hs);
				once.compos(x, 1);
			}
			return 1;
		};
		for (auto &x : body) {
			for (auto &y : face) {
				fup_range (dir, 0, 2) {
					once.compos(x, 0);
					once.compos(y, dir);
					once.compos(x, 1);
					if (add())
						comb.push_back(once);
					once.compos(x, 0);
					once.compos(y, dir ^ 1);
					once.compos(x, 1);
				}
			}
		}
	}
private:
	static pm origin;
};
CUBE_T
_1 CUBE_C::origin;

#undef CUBE_T
#undef CUBE_C

