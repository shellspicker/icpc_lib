#include <bits/stdc++.h>
using namespace std;
//using std::cin;
//using std::cout;
//using std::vector;
//using std::queue;
//using std::set;
//using std::reverse;
//using std::copy;
//using std::ostream_iterator;
//using std::initializer_list;
//using std::for_each;
//using std::transform;
//using std::accumulate;
//using std::generate;
//using std::is_permutation;
//using std::find_if;
//using std::find_if_not;
//using std::gcd;
//using std::lcm;
typedef long long ll;
typedef unsigned long long ull;

int gcd(int a, int b)
{
	return a == 0 ? b : gcd(b % a, a);
}

int lcm(int a, int b)
{
	return a * b / gcd(a, b);
}

const ull seed = 3137;

template <size_t dn>
class permutation
{
	public:
		static void init() {
			origin.assign(dn, 1);
			partial_sum(origin.begin(), origin.end(), origin.begin());
		}
		int mat[2][dn + 5];
		ull hs[2];
		vector<int> cycle[2][dn + 5];
		int cycn, period;
		permutation() {
			auto fn = [=, i = 1](void) mutable { return i++; };
			generate(mat[0] + 1, mat[0] + 1 + dn, fn);
			gall();
		}
		permutation(vector<int> &&p) { assign(p); }
		permutation(vector<int> &&pre, vector<int> &&nxt) { assign(pre, nxt); }
		void assign(vector<int> &&p) {
			assert(is_permutation(origin.begin(), origin.end(), p.begin()));
			copy(p.begin(), p.end(), mat[0] + 1);
			gall();
		}
		void assign(vector<int> &&pre, vector<int> &&nxt) {
			auto fn = [](int x) { return 1 <= x && x <= dn; };
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
			auto fn = [=](int x) { return x[rhs.mat[tp]]; };
			transform(mat[0] + 1, mat[0] + 1 + dn, mat[0] + 1, fn);
			gall();
		}
		void print() {
			cout << "\n!!! permutation's status: " << this << '\n';
			cout << "is perm? " << is_permutation(origin.begin(), origin.end(), mat[0] + 1) << '\n';
			cout << "period: " << period << '\n';
			for (int i = 0; i < 2; ++i) {
				copy(mat[i] + 1, mat[i] + 1 + dn, ostream_iterator<int>(cout, " "));
				cout << '\n';
				cout << "hs[" << i << "]: " << hs[i] << '\n';
				for_each(cycle[i] + 1, cycle[i] + 1 + cycn, [=](auto &v) {
						cout << '(';
						for (long j = 0; j < v.size(); ++j) {
						char delim = j ? ',' : 0;
						cout << delim << v[j];
						}
						cout << ')';
						});
				cout << '\n';
			}
		}
	private:
		static vector<int> origin;
		void gall() { ghs(); ginv(); gcyc(); }
		void ghs() {
			auto fn = [=](ull pre, ull now) { return pre * seed + now; };
			for (int i = 0; i < 2; ++i)
				hs[i] = accumulate(mat[i] + 1, mat[i] + 1 + dn, 0llu, fn);
		}
		void ginv() {
			auto fn = [=, i = 1](int x) mutable { mat[1][x] = i++; };
			for_each(mat[0] + 1, mat[0] + 1 + dn, fn);
		}
		void gcyc() {
			bool vis[dn + 5];
			cycn = 0;
			period = 1;
			memset(vis, 0, sizeof vis);
			for (int x = 1; x <= dn; ++x) {
				cycle[0][x].clear();
				cycle[1][x].clear();
				if (!vis[x]) {
					int nx = x;
					cycn++;
					while (!vis[nx]) {
						vis[nx] = 1;
						cycle[0][cycn].push_back(nx);
						cycle[1][cycn].push_back(nx);
						nx = mat[0][nx];
					};
					reverse(cycle[1][cycn].begin(), cycle[1][cycn].end());
					period = lcm(period, cycle[0][cycn].size());
				}
			}
		}
};

template <size_t dn>
using pm = permutation<dn>;
template <size_t dn>
using vpm = vector<permutation<dn>>;
template <size_t dn>
vector<int> permutation<dn>::origin;

template <size_t dn>
class cube
{
	public:
		pm<dn> origin;
		vpm<dn> face, body, buf;
		cube() {
			permutation<dn>::init();
			origin = pm<dn>();
		}
		void level_bfs(vpm<dn> &misc, int limit, vpm<dn> &comb) {
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
		void face_seq(vpm<dn> &body, vpm<dn> &face, vpm<dn> &comb) {
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

ull mul_mod(ull a, ull b, ull mod)
{
    //o(1)快速乘
    return (a * b - (long long)(a / (long double)mod * b + 1e-3) * mod + mod) % mod;
}

ull pow_mod(ull x, ull n, ull mod)
{
    ull res = 1;
    while(n)
    {
        if(n&1) res = mul_mod(res,x,mod);
        x = mul_mod(x,x,mod);
        n >>= 1;
    }
    return res;
}

cube<30> ccc;
int mmp[35];

void preprocess()
{
	ccc.face.resize(3);
	ccc.face[0].assign(
			{10,11,12,13,14,15,16,17,18,1,2,3,4,5,6,7,8,9,21,20,19,30,29,28,27,26,25,24,23,22});
	ccc.face[1].assign(
			{3,6,9,2,5,8,1,4,7,16,13,10,17,14,11,18,15,12,22,23,24,25,26,27,28,29,30,19,20,21});
	ccc.face[2].assign(
			{10,11,12,4,5,6,7,8,9,1,2,3,13,14,15,16,17,18,21,20,19,30,23,24,25,26,27,28,29,22});
	ccc.level_bfs(ccc.face, 100233, ccc.buf);
	memset(mmp, 0, sizeof mmp);
	for (int ci = 0; ci < ccc.buf.size(); ++ci) {
		auto xp = ccc.buf[ci];
		mmp[xp.cycn]++;
	}
}

void solve()
{
	int tc;
	ll n, p, mod, ans;

	cin >> tc;
	while (tc--) {
		cin >> n >> p;
		ans = 0;
		mod = p * ccc.buf.size();
		for (int x = 1; x <= 30; ++x) {
			ans = (ans + mmp[x] * pow_mod(n, x, mod) % mod) % mod;
		}
		ans /= ccc.buf.size();
		cout << ans << '\n';
	}
}

int
main()
{
	preprocess();
	solve();
	return 0;
}
