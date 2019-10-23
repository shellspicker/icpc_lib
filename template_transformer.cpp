template <size_t pn>
class permutation
{
public:
	static vector<int> origin;
	static void init();
	int ds[2][pn + 5];
	vector<int> mat[2][pn + 5];
	int loop_n, period;
	ull hs[2];
	permutation();
	permutation(vector<int>);
	permutation(vector<int>, vector<int>);
	void assign(vector<int>);
	void assign(vector<int>, vector<int>);
	void print();
	void trans(permutation<pn> &, int);
private:
	void fuck();
	void get_inverse();
	void get_hs();
	void get_matrix();
};

template <size_t pn>
vector<int> permutation<pn>::origin;

template <size_t pn>
void permutation<pn>::init()
{
	origin.assign(pn, 1);
	partial_sum(origin.begin(), origin.end(), origin.begin());
}

template <size_t pn>
permutation<pn>::permutation()
{
	generate(ds[0] + 1, ds[0] + 1 + pn, [=, i = 1](void) mutable {
				return i++;
			});
	fuck();
}

template <size_t pn>
permutation<pn>::permutation(vector<int> list)
{
	assign(list);
}
template <size_t pn>
permutation<pn>::permutation(vector<int> list1, vector<int> list2)
{
	assign(list1, list2);
}

template <size_t pn>
void permutation<pn>::assign(vector<int> list)
{
	copy(list.begin(), list.end(), ds[0] + 1);
	fuck();
}

template <size_t pn>
void permutation<pn>::assign(vector<int> list1, vector<int> list2)
{
	permutation();
	for (int i = 0; i < list1.size(); ++i) {
		ds[0][list1[i]] = list2[i];
	}
	fuck();
}

template <size_t pn>
void permutation<pn>::trans(permutation<pn> &tr, int type)
{
	transform(ds[0] + 1, ds[0] + 1 + pn, ds[0] + 1, [=](int x) {
			return x[tr.ds[type]];
			});
	fuck();
}

template <size_t pn>
void permutation<pn>::fuck()
{
	get_inverse();
	get_hs();
	get_matrix();
}

template <size_t pn>
void permutation<pn>::get_inverse()
{
	for_each(ds[0] + 1, ds[0] + 1 + pn, [=, this, i = 1](int &x) mutable {
				ds[1][x] = i++;
			});
}

template <size_t pn>
void permutation<pn>::get_matrix()
{
	bool vis[pn + 5];
	loop_n = 0;
	period = 1;
	memset(vis, 0, sizeof vis);
	for (int x = 1; x <= pn; ++x) {
		mat[0][x].clear();
		mat[1][x].clear();
		if (!vis[x]) {
			int nx = x;
			loop_n++;
			while (!vis[nx]) {
				vis[nx] = 1;
				mat[0][loop_n].push_back(nx);
				mat[1][loop_n].push_back(nx);
				nx = ds[0][nx];
			};
			reverse(mat[1][loop_n].begin(), mat[1][loop_n].end());
			period = lcm(period, mat[0][loop_n].size());
		}
	}
}

template <size_t pn>
void permutation<pn>::get_hs()
{
	for (int i = 0; i < 2; ++i)
		hs[i] = accumulate(ds[i] + 1, ds[i] + 1 + pn, 0llu, [=](ull pre, ull now) {
			return pre * seed + now;
			});
}

template <size_t pn>
void permutation<pn>::print()
{
	cout << "\n!!! permutation's status: " << this << '\n';
	cout << "is perm? " << is_permutation(origin.begin(), origin.end(), ds[0] + 1) << '\n';
	cout << "period: " << period << '\n';
	for (int i = 0; i < 2; ++i) {
		copy(ds[i] + 1, ds[i] + 1 + pn, ostream_iterator<int>(cout, " "));
		cout << '\n';
		cout << "hs[" << i << "]: " << hs[i] << '\n';
		for_each(mat[i] + 1, mat[i] + 1 + loop_n, [=](auto &v) {
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

template <size_t pn>
using perm = permutation<pn>;
template <size_t pn>
using vperm = vector<permutation<pn>>;

template <size_t pn>
class cube
{
public:
	perm<pn> origin;
	vperm<pn> face, body, buf;
	cube();
	void level_bfs(vperm<pn> &, int, vperm<pn> &);
	void face_seq(vperm<pn> &, vperm<pn> &, vperm<pn> &);
};

template <size_t pn>
cube<pn>::cube()
{
	perm<pn>::init();
	origin = perm<pn>();
}

template <size_t pn>
void cube<pn>::level_bfs(vperm<pn> &misc, int limit, vperm<pn> &comb)
{
	queue<perm<pn>> que[2];
	set<ull> st;
	int qid = 0;
	que[qid].push(origin);
	st.insert(origin.hs[0]);
	comb.push_back(origin);
	for (int lev = 0; lev < limit; ++lev) {
		if (que[qid].empty())
			break;
		while (!que[qid].empty()) {
			perm<pn> x = que[qid].front(); que[qid].pop();
			for (auto y : misc) {
				x.trans(y, 0);
				if (!st.count(x.hs[0])) {
					que[qid ^ 1].push(x);
					st.insert(x.hs[0]);
					comb.push_back(x);
				}
				x.trans(y, 1);
			}
		}
		qid ^= 1;
	}
}

template <size_t pn>
void cube<pn>::face_seq(vperm<pn> &body, vperm<pn> &face, vperm<pn> &comb)
{
	perm<pn> once = origin;
	set<ull> st;
	st.insert(once.hs[0]);
	comb.push_back(once);
	for (auto x : body) {
		for (auto y : face) {
			once.trans(x, 0);
			once.trans(y, 0);
			once.trans(x, 1);
			if (!st.count(x.hs[0])) {
				st.insert(x.hs[0]);
				comb.push_back(once);
			}
			once.trans(y, 1);
		}
	}
}
