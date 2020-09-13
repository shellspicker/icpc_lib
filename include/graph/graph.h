#pragma once

#pragma message \
usage_begin("graph.h") \
line("template<v_info, e_info>") \
line("v_info: 结点信息.") \
line("\t自定义的结构体.") \
line("e_info: 边信息.") \
line("\t自定义的结构体.") \
line("\t空构造函数写好默认边信息, 加边函数省略参数用.") \
usage_end()

template<typename v_info, typename e_info>
struct graph {
	struct node {
		int id;
		vector<int> eid;
		v_info info;
		node() {}
		node(int _1) : id(_1) {
			eid.clear();
		}
	};
	struct edge {
		int from, to;
		e_info info;
		edge() {}
		edge(int _1, int _2, e_info _3) : from(_1), to(_2), info(_3) {}
	};
	vector<node> nodes;
	vector<edge> edges;
	graph(int vn = 0) {
		clear();
		nodes.resize(vn);
		fup_range (i, 0, vn) {
			auto &nd = nodes[i];
			nd.id = i;
			nd.eid.clear();
		}
	}
	void clear() {
		nodes.clear();
		edges.clear();
	}
	void resize(int vn) {
		new (this) graph(vn);
	}
	void add(int from, int to, e_info e_if = e_info()) {
		assert(inrange(from, range(0, nodes.size())));
		assert(inrange(to, range(0, nodes.size())));
		edges.push_back({from, to, e_if});
		nodes[from].eid.push_back(edges.size() - 1);
	}
	void add2(int from, int to, e_info e_if = e_info()) {
		add(from, to, e_if);
		add(to, from, e_if);
	}
};
