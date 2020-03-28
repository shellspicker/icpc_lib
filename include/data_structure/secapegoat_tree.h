#ifndef SECAPEGOAT_TREE_H
#define SECAPEGOAT_TREE_H 1

#include "data_structure/bst.h"

/*
 * 替罪羊树.
 * 核心思想在rebuild, 暴力重构, 重构的条件可以微调, 和alpha有关.
 * 结点核心cover和exist, exist是删除的lazy tag,
 * size表示真实结点(不包括删除的点), cover表示虚拟结点(包括删除的点).
 * 需要重写搜索树的行为, 所有查找到当前结点的判断, 需要加上exist判断.
 * 不考虑order的重写, 简单写了kth和search, 和标准bst的查找行为(参数)有点偏差,
 * 之后看看能不能统一参数.
 * 现在是手动维护插入删除的结点变化, 没有调用pull.
 */
template<typename tp, size_t dsn, size_t pon>
class secapegoat : public bst<tp> {
	static constexpr double alpha = 0.75;
	class node : public bst<tp>::node {
	public:
		static node *null;
		using bst<tp>::node::ls;
		using bst<tp>::node::rs;
		using bst<tp>::node::size;
		int cover;
		bool exist;
		// 附加信息
		//int val;// map用.
		node() {}
		node(tp k) : bst<tp>::node(k) {
			cover = exist = 1;
		}
		bool bad() {
			return (cover * alpha + 5 < ((node *)ls)->cover) ||
				(cover * alpha + 5 < ((node *)rs)->cover);
		}
		node *pull() {
			size = ls->size + rs->size + exist;
			cover = ((node *)ls)->cover + ((node *)rs)->cover + 1;
			return this;
		}
	};
	allocator<node, pon> alloc;
	void rebuild(node *&t) {
		static vector<node *> v;
		function<void(node *)> visit = [&](node *t) {
			if (t == null)
				return;
			visit((node *)t->ls);
			if (t->exist) {
				v.emplace_back(t);
			} else {
				alloc(t);
			}
			visit((node *)t->rs);
		};
		function<void(node *&t, int l, int r)> divide = [&](node *&t, int l, int r) {
			if (length(l, r) == 0) {
				t = null;
				return;
			}
			int mid = midpoint(l, r);
			t = v[mid];
			divide((node *&)t->ls, l, mid - 1);
			divide((node *&)t->rs, mid + 1, r);
			t->pull();
		};
		v.clear();
		visit(t);
		divide(t, 0, v.size() - 1);
	}
	node **insert(node *&t, tp x) {
		node **ret;
		if (t == null) {
			t = new (alloc()) node(x);
			ret = &null;
		} else {
			bool d = t->key < x;// equal or not is don't care.
			t->size++, t->cover++;
			ret = insert((node *&)t->ch[d], x);
			if (t->bad())
				ret = &t;
		}
		return ret;
	}
	void remove(node *t, int k) {
		while (t != null) {
			t->size--;
			int s = t->ls->size + t->exist;
			if (t->exist && k == s) {
				t->exist = 0;
				break;
			}
			bool ok = s < k;
			t = (node *)t->ch[ok];
			if (ok)
				k -= s;
		}
	}
public:
	node *root[dsn], *&null = node::null;// null must be reference.
	void init() {
		alloc.clear();
		null = new (alloc()) node(-1);
		bst<tp>::null = null;
		null->size = null->cover = 0;
		null->ls = null->rs = null;
		fup (i, 0, dsn - 1)
			root[i] = null;
	}
	node *&operator ()(int idx) {
		return root[idx];
	}
	void insert(int tid, tp x) {
		node **fix = insert(root[tid], x);
		if (*fix != null)
			rebuild(*fix);
	}
	void remove(int tid, tp x) {
		node *&t = root[tid];
		int k = search(t, x);
		if (kth(t, k)->key ^ x)
			return;
		remove(t, k);
		if (t->size < t->cover * alpha)
			rebuild(t);
	}
	node *kth(node *o, int k) {
		while (o != null) {
			int s = o->ls->size + o->exist;
			if (o->exist && k == s)
				return o;
			bool ok = s < k;
			o = (node *)o->ch[ok];
			if (ok)
				k -= s;
		}
		return null;
	}
	int search(node *o, tp x) {
#define dwn(cond) \
		if ((cond)) ans += o->ls->size + o->exist, o = (node *)o->rs;\
		else o = (node *)o->ls
		int ans = 1;// 从1开始标号.
		while (o != null) {
			dwn(o->key < x);
		}
		return ans;
#undef dwn
	}
};
template<typename tp, size_t dsn, size_t pon>
typename secapegoat<tp, dsn, pon>::node *secapegoat<tp, dsn, pon>::node::null;

#endif
