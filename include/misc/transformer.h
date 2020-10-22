#pragma once

#define PERMUTATAION_T template<size_t _1>
#define PERMUTATAION_C permutation<_1>

template<size_t dn>
class permutation {
public:
	static void init() {
		iota(origin, origin + dn, 0);
	}
	permutation() {
		iota(mat[0], mat[0] + dn, 0);
		gall();
	}
	permutation(const vector<int> &p) { assign(p); }
	permutation(const vector<int> &pre, const vector<int> &nxt) { assign(pre, nxt); }
	void assign(const vector<int> &p) {
		assert(is_permutation(origin, origin + dn, p.begin()));
		copy(p.begin(), p.end(), mat[0]);
		gall();
	}
	void assign(const vector<int> &pre, const vector<int> &nxt) {
		auto fn = [](int x) { return inrange(x, 0, int(dn - 1)); };
		assert(find_if_not(pre.begin(), pre.end(), fn) == pre.end());
		assert(find_if_not(nxt.begin(), nxt.end(), fn) == nxt.end());
		assert(is_permutation(pre.begin(), pre.end(), nxt.begin()));
		permutation();
		fup (i, 0, pre.size() - 1)
			mat[0][pre[i]] = nxt[i];
		gall();
	}
	void compos(permutation<dn> &rhs, int tp) {
		auto fn = [=](int x) { return rhs.mat[tp][x]; };
		transform(mat[0], mat[0] + dn, mat[0], fn);
		gall();
	}
	int mat[2][dn];
	ull hs[2];
	vector<int> cycle[2][dn];
	int cycn, period;
private:
	void gall() { ghs(); ginv(); gcyc(); }
	void ghs() {
		for (int i = 0; i < 2; ++i)
			hs[i] = hash_val(vector<int>(mat[i], mat[i] + dn));
	}
	void ginv() {
		int i = 0;
		auto fn = [&](int x) { mat[1][x] = i++; };
		for_each(mat[0], mat[0] + dn, fn);
	}
	void gcyc() {
		bool vis[dn];
		cycn = 0;
		period = 1;
		memset(vis, 0, sizeof vis);
		fup (x, 0, dn - 1) {
			cycle[0][x].clear();
			cycle[1][x].clear();
			if (!vis[x]) {
				int nx = x;
				while (!vis[nx]) {
					vis[nx] = 1;
					cycle[0][cycn].push_back(nx);
					cycle[1][cycn].push_back(nx);
					nx = mat[0][nx];
				};
				reverse(cycle[1][cycn].begin(), cycle[1][cycn].end());
				period = lcm(period, int(cycle[0][cycn].size()));
				cycn++;
			}
		}
	}
	static int origin[dn];
};
PERMUTATAION_T
int PERMUTATAION_C::origin[_1];

#undef PERMUTATAION_T
#undef PERMUTATAION_C

#define CUBE_T template<size_t _1>
#define CUBE_C cube<_1>

template<size_t dn>
class cube
{
public:
	using pm = permutation<dn>;
	using vpm = vector<permutation<dn>>;
	static void init() {
		pm::init();
		origin = pm();
	}
	static void level_bfs(vpm &comb, vpm &misc, int limit) {
		queue<pm> qnow, qnxt;
		set<ull> st;
		qnow.push(origin);
		st.insert(origin.hs[0]);
		comb.push_back(origin);
		for (int lev = 0; lev < limit; ++lev) {
			if (qnow.empty())
				break;
			while (!qnow.empty()) {
				pm x = qnow.front(); qnow.pop();
				for (auto y : misc) {
					x.compos(y, 0);
					if (!st.count(x.hs[0])) {
						qnxt.push(x);
						st.insert(x.hs[0]);
						comb.push_back(x);
					}
					x.compos(y, 1);
				}
			}
			qnow.swap(qnxt);
		}
	}
	static void face_seq(vpm &comb, vpm &body, vpm &face) {
		pm once = origin;
		set<ull> st;
		st.insert(once.hs[0]);
		comb.push_back(once);
		for (auto x : body) {
			for (auto y : face) {
				once.compos(x, 0);
				once.compos(y, 0);
				once.compos(x, 1);
				if (!st.count(x.hs[0])) {
					st.insert(x.hs[0]);
					comb.push_back(once);
				}
				once.compos(y, 1);
			}
		}
	}
private:
	static pm origin;
};
CUBE_T
typename CUBE_C::pm CUBE_C::origin;

#undef CUBE_T
#undef CUBE_C
