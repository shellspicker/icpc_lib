template<size_t dn>
class permutation
{
	static int origin[dn + 1];
	void gall() { ghs(); ginv(); gcyc(); }
	void ghs() {
		for (int i = 0; i < 2; ++i)
			hs[i] = hash_val(vector<int>(mat[i], mat[i] + dn));
	}
	void ginv() {
		auto fn = [=, i = 0](int x) mutable { mat[1][x] = i++; };
		for_each(mat[0], mat[0] + dn, fn);
	}
	void gcyc() {
		bool vis[dn + 1];
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
				period = lcm(period, cycle[0][cycn].size());
				cycn++;
			}
		}
	}
public:
	static void init() {
		auto fn = [=, i = 0](void) mutable { return i++; };
		generate(origin, origin + dn, fn);
	}
	int mat[2][dn + 1];
	ull hs[2];
	vector<int> cycle[2][dn + 1];
	int cycn, period;
	permutation() {
		auto fn = [=, i = 0](void) mutable { return i++; };
		generate(mat[0], mat[0] + dn, fn);
		gall();
	}
	permutation(vector<int> &&p) { assign(p); }
	permutation(vector<int> &&pre, vector<int> &&nxt) { assign(pre, nxt); }
	void assign(vector<int> &&p) {
		assert(is_permutation(origin, origin + dn, p.begin()));
		copy(p.begin(), p.end(), mat[0]);
		gall();
	}
	void assign(vector<int> &&pre, vector<int> &&nxt) {
		auto fn = [](int x) { return 0 <= x && x <= dn - 1; };
		assert(find_if_not(pre.begin(), pre.end(), fn) == pre.end());
		assert(find_if_not(nxt.begin(), nxt.end(), fn) == nxt.end());
		assert(is_permutation(pre.begin(), pre.end(), nxt.begin()));
		permutation();
		for (int i = 0; i < pre.size(); ++i) {
			mat[0][pre[i]] = nxt[i];
		}
		gall();
	}
	void compos(permutation<dn> &rhs, int tp) {
		auto fn = [=](int x) { return rhs.mat[tp][x]; };
		transform(mat[0], mat[0] + dn, mat[0], fn);
		gall();
	}
};
template<size_t dn>
int permutation<dn>::origin[];
template<size_t dn>
using pm = permutation<dn>;
template<size_t dn>
using vpm = vector<permutation<dn>>;

template<size_t dn>
class cube
{
	static pm<dn> origin;
public:
	static void init() {
		permutation<dn>::init();
		origin = pm<dn>();
	}
	static void level_bfs(vpm<dn> &misc, int limit, vpm<dn> &comb) {
		queue<pm<dn>> que[2];
		set<ull> st;
		int qid = 0;
		que[qid].push(origin);
		st.insert(origin.hs[0]);
		comb.push_back(origin);
		for (int lev = 0; lev < limit; ++lev) {
			if (que[qid].empty())
				break;
			while (!que[qid].empty()) {
				pm<dn> x = que[qid].front(); que[qid].pop();
				for (auto y : misc) {
					x.compos(y, 0);
					if (!st.count(x.hs[0])) {
						que[qid ^ 1].push(x);
						st.insert(x.hs[0]);
						comb.push_back(x);
					}
					x.compos(y, 1);
				}
			}
			qid ^= 1;
		}
	}
	static void face_seq(vpm<dn> &body, vpm<dn> &face, vpm<dn> &comb) {
		pm<dn> once = origin;
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
};
template<size_t dn>
pm<dn> cube<dn>::origin;
