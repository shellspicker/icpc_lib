# graph

图信息类.

[代码](../../../include/graph/graph.h)

## classes

| name                                          | description           |
| --------------------------------------------- | --------------------- |
| [graph](detail/classes/graph/readme.md)       | 可自定义信息的图.     |

### 图

### synopsis

```c++
template<typename nif, typename eif>
struct graph {
	struct node {
		static graph_node *base_addr;
		vector<int> link;
		nif meta;
		node() : link(vector<int>()), meta(nif());
		int id();
	};
	struct edge {
		int from, to;
		eif meta;
		edge();
		edge(int from, int to, eif ext = eif());
	};
	vector<node> nodes;
	vector<edge> edges;
	node *&node_base;
	graph(int vn = 0);
	node &operator [](int i);
	void clear();
	int size();
	void resize();
	void add(int from, int to, eif meta = eif());
	void add2(int from, int to, eif meta = eif());
	void add_edge_only(int from, int to, eif meta = eif());
	pair<node *, edge *> extend(int i);
};
```
