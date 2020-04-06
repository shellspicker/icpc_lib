#ifndef SBT_H
#define SBT_H 1

#define FATHER 1
#include "data_structure/bst.h"

/*
 * sbt.
 * 详细参考陈启锋论文"Size Balanced Tree".
 * 核心思想在于maintain.
 * remove和treap不一样.
 */
template<typename tp, size_t dsn, size_t pon>
class sbt : public bst<tp> {
#define ls ch[0]
#define rs ch[1]
#if FATHER
#  define link(u, d, v) ((u->ch[d] = v)->fa = u)
#else
#  define link(u, d, v) ((u->ch[d] = v), u)
#endif
	class node : public bst<tp>::node {
	public:
		static node *null;
		// 附加信息
		//int val;// map用.
		node() {}
		node(tp k) : bst<tp>::node(k) {}
	};
	allocator<node, pon> alloc;
	// d方向的子结点旋转上来.
	void rotate(node *&t, int d) {
		node *k = (node *)t->ch[d];
#if FATHER
		node *ac = (node *)t->fa;
#endif
		link(t, d, k->ch[d ^ 1])->pull();
		link(k, d ^ 1, t);
#if FATHER
		link(ac, ac->rs == t, k);
#endif
		t = k;
	}
	void maintain(node *&t, int d) {
		if (t->ch[d] == null)
			goto end;
		if (t->ch[d ^ 1]->size < t->ch[d]->ch[d]->size) {
			rotate(t, d);
		} else if(t->ch[d ^ 1]->size < t->ch[d]->ch[d ^ 1]->size) {
			rotate((node *&)t->ch[d], d ^ 1);
			rotate(t, d);
		} else {
			goto end;
		}
		maintain((node *&)t->ch[d], d);
		maintain((node *&)t->ch[d ^ 1],d ^ 1);
		maintain(t, 0);
		maintain(t, 1);
end:
		t->pull();
	}
	node *insert(node *&t, tp x) {
		if (t==null) {
			t = new (alloc()) node(x);
		} else {
			bool d = t->key < x;// equal or not is don't care.
			insert((node *&)t->ch[d], x)->fa = t;
			maintain(t, d);
		}
		return t;
	}
	// 返回删除的值, 模糊查找, 删除的值可以不在树里面.
	tp remove(node *&t, tp x) {
		if (t == null)
			return 0;
		int ret;
		/*
		 * case1: 找到合适的1个点.
		 * case2: 还在查找的途中.
		 */
		if (x == t->key || (x < t->key && t->ls == null) || (t->key < x && t->rs == null)) {
			// case1.
			ret = t->key;// 此点必定被删除
			if(t->ls == null || t->rs == null) {// 对应后面2个条件, 删除的不一定是准确值.
				alloc(t);
				node *tmp = t->ls != null? (node *)t->ls: (node *)t->rs;
				tmp->fa = t->fa;
				t = tmp;
			} else {
				// 替换成子树中最接近当前结点的值.
				bool d = t->ls->size > t->rs->size;
				t->key = remove((node *&)t->ch[d], t->key + (!d ? 1 : -1));
			}
		} else {
			// case2:
			ret = remove((node *&)t->ch[t->key < x], x);
		}
		if (t != null)
			t->pull();
		return ret;
	}
public:
	node *root[dsn], *&null = node::null;// null must be reference.
	void init() {
		alloc.clear();
		null = new (alloc()) node(-1);
		bst<tp>::null = null;
		null->size = 0;
		null->ls = null->rs = null;
		fup (i, 0, dsn - 1)
			root[i] = null;
	}
	node *&operator ()(int idx) {
		return root[idx];
	}
	void insert(int tid, tp x) {
		insert(root[tid], x);
	}
	void remove(int tid, tp x) {
		auto fd = bst<tp>::search(root[tid], x, 0, 1);
		if (fd.second == null)
			return;
		remove(root[tid], x);
	}
#undef ls
#undef rs
#undef link
};
template<typename tp, size_t dsn, size_t pon>
typename sbt<tp, dsn, pon>::node *sbt<tp, dsn, pon>::node::null;

#endif
