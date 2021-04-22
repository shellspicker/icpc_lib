/*
 * 随机二叉树
 *
 * include:
 *   basic/rand.h
 *   data_structure/dsu.h
 *   graph/graph.h
 */
class random_binary_tree {
	struct vif {
		int ind, outd;
		vif() : ind(0), outd(0) {}
	};
	random_int<int> rd_int;
	graph<vif, fake_type> grp;
	dsu gid;
	int root;
public:
	random_binary_tree(int vn = 0) { resize(vn); }
	void resize(int vn) {
		rd_int.set(0, vn - 1);
		grp.resize(vn);
		gid.init(vn);
		root = rd_int();
	}
	void gao() {
		int remain_edges = grp.size() - 1;
		while (remain_edges) {
			int a, b;
			do {
				a = rd_int();
				b = rd_int();
				if ((a == b) ||
					(gid.set(a) == gid.set(b)))
					continue;
				if (a == root || b == root) {
					int other = a == root ? b : a;
					if (grp[other].meta.ind == 1 || grp[root].meta.outd == 2)
						continue;
					grp[other].meta.ind++;
					grp[root].meta.outd++;
				} else {
					if (grp[a].meta.outd < 2 && grp[b].meta.ind < 1) {
						grp[a].meta.outd++;
						grp[b].meta.ind++;
					} else if (grp[b].meta.outd < 2 && grp[a].meta.ind < 1) {
						grp[b].meta.outd++;
						grp[a].meta.ind++;
					} else {
						continue;
					}
				}
				grp.add2(a, b);
				gid.link(a, b);
				remain_edges--;
			} while (0);
		}
	}
	void print() {
		gid.init(grp.size());
		assert(grp.edges.size() == (grp.size() - 1) * 2);
		fup_range (u, 0, grp.size()) {
			if (u == root)
				assert(grp[u].meta.ind == 0);
			else
				assert(grp[u].meta.ind == 1);
			assert(grp[u].meta.outd <= 2);
		}
		fio.msg("%d %d\n", root, grp.size());
		fup_range_s (i, 0, grp.edges.size(), 2) {
			auto e = grp.edges[i];
			fio.msg("%d %d\n", e.from, e.to);
			assert(!gid.same(e.from, e.to));
			gid.link(e.from, e.to);
		}
	}
};

