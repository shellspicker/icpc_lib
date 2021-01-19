# graph

图信息类.

[代码](../../../../../../include/graph/graph.h)

## 头文件

```c++
#include "graph/graph.h"
```

## 用法

通过内嵌2个结构体, 在内部表示图中点/边的额外信息.  
如果不需要额外信息, 请使用`fake_type`结构体(见`icpc_lib/include/template.h`).  
建议在额外信息的结构体里写默认构造函数的行为, 方便一些默认值的设置.

## 示例代码

以一个树的dfs为例.

```c++
struct nif {
	/*
	 * 点的额外信息.
	 * 最好写上默认构造函数.
	 */
};
struct eif {
	/*
	 * 边的额外信息.
	 * 最好写上默认构造函数.
	 */
};
using graph_t = graph<nif, eif>;
using node = graph_t::node;
using edge = graph_t::edge;

graph_t grp;

void dfs(int u, int fa)
{
	node *v;
	edge *e;
	grp[u].meta ... // 点的额外信息访问.
	for (int ei : grp[u].link) {
		tie(v, e) = grp.extend(ei);
		v->meta ... // 点的额外信息访问.
		e->meta ... // 边的额外信息访问.
		if (v->id() == fa)
			continue;
		dfs(v->id(), u);
	}
}

int main()
{
	grp.resize(10);
	fup_range (i, 0, grp.size()) {
		printf("%d\n", grp[i].id());
		grp.add(0, i);
		edge e = {...};
		grp.add(0, i, e);
	}
	fup_range (i, 0, grp.edges.size) {
		edge &e = grp.edges[i];
		printf("%d->%d\n", e.from, e.to);
	}
	dfs(0, -1);
	return 0;
}
```

最初的类型信息定义注意了, 几个`using`很重要.

遍历相邻点和边的时候用到`extend`函数.

访问额外信息用到meta的成员, 类型就是模板参数里面传来的结构体.
