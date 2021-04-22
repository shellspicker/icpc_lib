#define FAST_IO 1

#include "template.h"
#include "graph/graph.h"

using graph_t = graph<fake_type, fake_type>;
using node = graph_t::node;
using edge = graph_t::edge;

int root, vn;
graph_t grp;
struct binary_node {
	binary_node() {
		ls = rs = 0;
		vis = 0;
	}
	binary_node *ls, *rs;
	int id;
	bool vis;
};
vector<binary_node> tree;

class test_dfs_pre {
public:
	static
	vector<int>
	run() {
		vector<int> ret;
		function<void(binary_node *)> dfs = [&](binary_node *u) {
			if (!u || u->vis)
				return;
			u->vis = 1;
			ret.push_back(u->id);
			dfs(u->ls);
			dfs(u->rs);
		};
		fup_range (i, 0, vn)
			tree[i].vis = 0;
		dfs(&tree[root]);
		return ret;
	}
};

class test_dfs_in {
public:
	static
	vector<int>
	run() {
		vector<int> ret;
		function<void(binary_node *)> dfs = [&](binary_node *u) {
			if (!u || u->vis)
				return;
			u->vis = 1;
			dfs(u->ls);
			ret.push_back(u->id);
			dfs(u->rs);
		};
		fup_range (i, 0, vn)
			tree[i].vis = 0;
		dfs(&tree[root]);
		return ret;
	}
};

class test_dfs_post {
public:
	static
	vector<int>
	run() {
		vector<int> ret;
		function<void(binary_node *)> dfs = [&](binary_node *u) {
			if (!u || u->vis)
				return;
			u->vis = 1;
			dfs(u->ls);
			dfs(u->rs);
			ret.push_back(u->id);
		};
		fup_range (i, 0, vn)
			tree[i].vis = 0;
		dfs(&tree[root]);
		return ret;
	}
};

class test_norec_pre {
public:
	static
	vector<int>
	run() {
		vector<int> ret;
		auto norec = [&](binary_node *u) {
			struct rgst {
				int phase;
				binary_node *o;
			};
			stack<rgst> st;
			st.push({0, u});
			while (!st.empty()) {
				auto &reg = st.top();
				switch (reg.phase) {
				case 0:
					if (!reg.o || reg.o->vis)
						break;
					reg.o->vis = 1;
					ret.push_back(reg.o->id);
					st.push({0, reg.o->ls});
					reg.phase = 1;
					continue;
				case 1:
					st.push({0, reg.o->rs});
					reg.phase = -1;
					continue;
				default:
					break;
				}
				st.pop();
			}
		};
		fup_range (i, 0, vn)
			tree[i].vis = 0;
		norec(&tree[root]);
		return ret;
	}
};

class test_norec_in {
public:
	static
	vector<int>
	run() {
		vector<int> ret;
		auto norec = [&](binary_node *u) {
			struct rgst {
				int phase;
				binary_node *o;
			};
			stack<rgst> st;
			st.push({0, u});
			while (!st.empty()) {
				auto &reg = st.top();
				switch (reg.phase) {
				case 0:
					if (!reg.o || reg.o->vis)
						break;
					reg.o->vis = 1;
					st.push({0, reg.o->ls});
					reg.phase = 1;
					continue;
				case 1:
					ret.push_back(reg.o->id);
					st.push({0, reg.o->rs});
					reg.phase = -1;
					continue;
				default:
					break;
				}
				st.pop();
			}
		};
		fup_range (i, 0, vn)
			tree[i].vis = 0;
		norec(&tree[root]);
		return ret;
	}
};

class test_norec_post {
public:
	static
	vector<int>
	run() {
		vector<int> ret;
		auto norec = [&](binary_node *u) {
			struct rgst {
				int phase;
				binary_node *o;
			};
			stack<rgst> st;
			st.push({0, u});
			while (!st.empty()) {
				auto &reg = st.top();
				switch (reg.phase) {
				case 0:
					if (!reg.o || reg.o->vis)
						break;
					reg.o->vis = 1;
					st.push({0, reg.o->ls});
					reg.phase = 1;
					continue;
				case 1:
					st.push({0, reg.o->rs});
					reg.phase = 2;
					continue;
				case 2:
					ret.push_back(reg.o->id);
					reg.phase = -1;
				default:
					break;
				}
				st.pop();
			}
		};
		fup_range (i, 0, vn)
			tree[i].vis = 0;
		norec(&tree[root]);
		return ret;
	}
};

void make_binary_tree()
{
	queue<int> que;
	tree.assign(vn, binary_node());
	que.push(root);
	node *v;
	edge *e;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		binary_node *o = &tree[u];
		o->vis = 1;
		o->id = u;
		for (int ei : grp[u].link) {
			tie(v, e) = grp.extend(ei);
			binary_node *x = &tree[v->id()];
			if (x->vis)
				continue;
			if (!o->ls)
				o->ls = x;
			else
				o->rs = x;
			que.push(v->id());
		}
	}
}

void print(const vector<int> &v)
{
	fup_range (i, 0, v.size())
		fio.msg("%d%c", v[i], " \n"[i == v.size() - 1]);
}

int main(int argc, char **argv)
{
	fio.in(root, vn);
	grp.resize(vn);
	fup (t, 1, vn - 1) {
		int a, b;
		fio.in(a, b);
		grp.add2(a, b);
	}
	make_binary_tree();

	assert(test_dfs_pre::run() == test_norec_pre::run());
	assert(test_dfs_in::run() == test_norec_in::run());
	assert(test_dfs_post::run() == test_norec_post::run());
	return 0;
}
