/*
 * 随机数生成器, 整数版本.
 */
template<typename tp, class twist = mt19937_64>
class random_int {
	using dist = uniform_int_distribution<tp>;
	dist segment;
	twist gen;
public:
	random_int() {
		srand(time(0));
		new (&gen) twist{(size_t)rand()};
	}
	void set(tp l, tp r) {
		new (&segment) dist{l, r};
	}
	pair<tp, tp> get() {
		assert(segment.a() == segment.min());
		assert(segment.b() == segment.max());
		return {segment.a(), segment.b()};
	}
	tp operator ()() {
		return segment(gen);
	}
};
/*
 * 随机数生成器, 浮点数版本.
 */
template<typename tp, class twist = mt19937_64>
class random_real {
	using dist = uniform_real_distribution<tp>;
	dist segment;
	twist gen;
public:
	random_real() {
		srand(time(0));
		new (&gen) twist{(size_t)rand()};
	}
	void set(tp l, tp r) {
		new (&segment) dist{l, r};
	}
	pair<tp, tp> get() {
		assert(segment.a() == segment.min());
		assert(segment.b() == segment.max());
		return {segment.a(), segment.b()};
	}
	tp operator ()() {
		return segment(gen);
	}
};
/*
 * 随机字符串生成器.
 *
 * 现在还很简单, 只开启了小写字母随机.
 */
class random_string {
	random_int<int> rd_numer, rd_lower, rd_upper;
public:
	random_string() {
		rd_lower.set('a', 'z');
		rd_upper.set('A', 'Z');
		rd_numer.set('0', '9');
	}
	string ref;
	void rand_len(int len) {
		ref.clear();
		ref.resize(len);
		fup_range (i, 0, len)
			ref[i] = rd_lower();
	}
	void repeat(int time) {
		time--;
		string tmp(ref);
		fup_range (t, 0, time)
			ref += tmp;
	}
	void cycle(int cyc, int len) {
		assert(len / cyc * cyc == len);
		int rep = len / cyc;
		rand_len(cyc);
		repeat(rep);
	}
	void swap(int pos) {
		string tmp(ref);
		ref = tmp.substr(pos) + tmp.substr(0, pos);
	}
};
/*
 * 随机二叉树
 */
/*
class random_binary_tree {
	random_int<int> rd_int;
	undigraph<int> g;
	dsu group;
	vector<int> deg_in, deg_out;
	int root;
public:
	random_binary_tree(int vn = 0) { resize(vn); }
	void resize(int vn) {
		rd_int.set(0, vn - 1);
		g.resize(vn);
		group.init(vn);
		deg_in.assign(vn, 0);
		deg_out.assign(vn, 0);
		root = rd_int();
	}
	void gao() {
		int remain_edges = g.n - 1;
		while (remain_edges) {
			int a, b;
			do {
				a = rd_int();
				b = rd_int();
				if ((a == b) ||
					(group.set(a) == group.set(b)))
					continue;
				if (a == root || b == root) {
					int other = a == root ? b : a;
					if (deg_in[other] == 1 || deg_out[root] == 2)
						continue;
					deg_out[root]++;
					deg_in[other]++;
				} else {
					if (deg_out[a] < 2 && deg_in[b] < 1) {
						deg_out[a]++;
						deg_in[b]++;
					} else if (deg_out[b] < 2 && deg_in[a] < 1) {
						deg_out[b]++;
						deg_in[a]++;
					} else {
						continue;
					}
				}
				g.add(a, b);
				group.link(a, b);
				remain_edges--;
			} while (0);
		}
	}
	void print() {
		assert(g.edges.size() == (g.n - 1) * 2);
		fup_range (i, 0, g.n) {
			if (i == root)
				assert(deg_in[i] == 0);
			else
				assert(deg_in[i] == 1);
			assert(deg_out[i] <= 2);
		}
		fio.msg("%d %d\n", root, g.n);
		fup_range_s (i, 0, g.edges.size(), 2) {
			auto e = g.edges[i];
			fio.msg("%d %d\n", e.from, e.to);
		}
	}
};
*/

