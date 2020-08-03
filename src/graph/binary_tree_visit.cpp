#define FAST_IO 1

#include "template.h"
#include "graph/graph.h"

undigraph<int> g;
int root, vn;
vector<int> vis;
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

void dfs_pre(binary_node *u) {
	if (!u || u->vis)
		return;
	u->vis = 1;
	fio.msg("%d\n", u->id);
	dfs_pre(u->ls);
	dfs_pre(u->rs);
}

void dfs_in(binary_node *u) {
	if (!u || u->vis)
		return;
	u->vis = 1;
	dfs_in(u->ls);
	fio.msg("%d\n", u->id);
	dfs_in(u->rs);
}

void dfs_post(binary_node *u) {
	if (!u || u->vis)
		return;
	u->vis = 1;
	dfs_post(u->ls);
	dfs_post(u->rs);
	fio.msg("%d\n", u->id);
}

void norec_pre(binary_node *u) {
	struct rgst {
		int phase;
		binary_node *o;
	};
	vector<rgst> st;
	st.push_back({0, u});

	/*
	 * 此为非递归框架, phase要自己从递归的代码拆分, phase之间转移类似自动机.
	 * push在phase前, 且phase标记后没有while(1)套着switch.
	 * 继续当前层: phase.
	 * 下一层: push.
	 * 上一层: pop.
	 */
	for (;;) {
push:
		auto &reg = st.back();
phase:
		switch (reg.phase) {
		case 0:
			if (!reg.o || reg.o->vis)
				goto pop;
			reg.o->vis = 1;
			reg.phase = 1;
			fio.msg("%d\n", reg.o->id);
			goto phase;
		case 1:
			st.push_back({0, reg.o->ls});
			reg.phase = 2;
			goto push;
		case 2:
			st.push_back({0, reg.o->rs});
			reg.phase = 3;
			goto push;
		case 3:
		}
pop:
		st.pop_back();
		if (st.empty())
			break;
	}
}

void norec_in(binary_node *u) {
	struct rgst {
		int phase;
		binary_node *o;
	};
	vector<rgst> st;
	st.push_back({0, u});

	/*
	 * 此为非递归框架, phase要自己从递归的代码拆分, phase之间转移类似自动机.
	 * push在phase前, 且phase标记后没有while(1)套着switch.
	 * 继续当前层: phase.
	 * 下一层: push.
	 * 上一层: pop.
	 */
	for (;;) {
push:
		auto &reg = st.back();
phase:
		switch (reg.phase) {
		case 0:
			if (!reg.o || reg.o->vis)
				goto pop;
			reg.o->vis = 1;
			reg.phase = 1;
			goto phase;
		case 1:
			st.push_back({0, reg.o->ls});
			reg.phase = 2;
			goto push;
		case 2:
			fio.msg("%d\n", reg.o->id);
			st.push_back({0, reg.o->rs});
			reg.phase = 3;
			goto push;
		case 3:
		}
pop:
		st.pop_back();
		if (st.empty())
			break;
	}
}

void norec_post(binary_node *u) {
	struct rgst {
		int phase;
		binary_node *o;
	};
	vector<rgst> st;
	st.push_back({0, u});

	/*
	 * 此为非递归框架, phase要自己从递归的代码拆分, phase之间转移类似自动机.
	 * push在phase前, 且phase标记后没有while(1)套着switch.
	 * 继续当前层: phase.
	 * 下一层: push.
	 * 上一层: pop.
	 */
	for (;;) {
push:
		auto &reg = st.back();
phase:
		switch (reg.phase) {
		case 0:
			if (!reg.o || reg.o->vis)
				goto pop;
			reg.o->vis = 1;
			reg.phase = 1;
			goto phase;
		case 1:
			st.push_back({0, reg.o->ls});
			reg.phase = 2;
			goto push;
		case 2:
			st.push_back({0, reg.o->rs});
			reg.phase = 3;
			goto push;
		case 3:
			fio.msg("%d\n", reg.o->id);
		}
pop:
		st.pop_back();
		if (st.empty())
			break;
	}
}

void debug_graph() {
	assert(g.n == vn);
	assert(g.edges.size() == (vn - 1) * 2);
	fup_range (i, 0, g.n) {
		fio.msg("size %d: %d\n", i, g[i].size());
		for (auto ei : g[i]) {
			auto e = g.info(ei);
			fio.msg("link %d->%d\n", e.from, e.to);
		}
	}
}

void make_binary_tree() {
	queue<int> que;
	tree.assign(vn, binary_node());
	que.push(root);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		binary_node *o = &tree[u];
		o->vis = 1;
		o->id = u;
		for (auto ei : g[u]) {
			auto e = g.info(ei);
			binary_node *x = &tree[e.to];
			if (x->vis)
				continue;
			if (!o->ls)
				o->ls = x;
			else
				o->rs = x;
			que.push(e.to);
		}
	}
}

void test_dfs() {
	make_binary_tree();
	fup_range (i, 0, vn)
		tree[i].vis = 0;
	dfs_in(&tree[root]);
}

void test_dfs_norec() {
	make_binary_tree();
	fup_range (i, 0, vn)
		tree[i].vis = 0;
	norec_post(&tree[root]);
}

int main(int argc, char **argv)
{
	fio.in(root, vn);
	g.resize(vn);
	fup (t, 1, vn - 1) {
		int a, b;
		fio.in(a, b);
		g.add(a, b);
	}
	//test_dfs();
	test_dfs_norec();
	return 0;
}
