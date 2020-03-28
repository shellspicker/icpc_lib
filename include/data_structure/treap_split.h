#ifndef TREAP_SPLIT_H
#define TREAP_SPLIT_H 1

#include "data_structure/bst.h"

/*
 * treap, split_merge, bst.
 * 优先级用系统的rand.
 * 这里是大顶堆, merge的时候都会判断堆的性质, 需要改的话找merge函数.
 */
template<typename tp, size_t dsn, size_t pon>
class treap : public bst<tp> {
	class node : public bst<tp>::node {
	public:
		static node *null;
		int fix;
		// 附加信息
		//int val;// map用.
		node() {}
		node(tp k) : bst<tp>::node(k) {
			fix = rand();
		}
	};
	allocator<node, pon> alloc;
	node *link(node *fa, node *son) {
		son->fa = fa;
		return fa;
	}
	pair<node *, node *> split_by_val(node *t, tp x) {
		if (t == null)
			return {null, null};
		node *lo, *ro;
		if (t->key <= x) {// note: <=.
			tie(lo, ro) = split_by_val((node *)t->rs, x);
			return {(node *)link(t, (node *)(t->rs = lo))->pull(), ro};
		} else {
			tie(lo, ro) = split_by_val((node *)t->ls, x);
			return {lo, (node *)link(t, (node *)(t->ls = ro))->pull()};
		}
	}
	node *merge(node *lo, node *ro) {
		if (lo == null || ro == null)
			return lo == null ? ro : lo;
		if (lo->fix > ro->fix) {// heap.
			return (node *)link(lo, (node *)(lo->rs = merge((node *)lo->rs, ro)))->pull();
		} else {
			return (node *)link(ro, (node *)(ro->ls = merge(lo, (node *)ro->ls)))->pull();
		}
	}
	void insert(node *&t, int x) {
		node *lo, *ro;
		tie(lo, ro) = split_by_val(t, x);
		t = merge(merge(lo, new (alloc()) node(x)), ro);
	}
	void remove(node *&t, int x) {
		node *lo, *mo, *ro;
		tie(lo, mo) = split_by_val(t, x - 1);
		tie(mo, ro) = split_by_val(mo, x);
		alloc(mo);
		t = merge(merge(lo, merge((node *)mo->ls, (node *)mo->rs)), ro);
	}
public:
	node *&null = node::null;// null must be reference.
	node *root[dsn];
	void init() {
		srand(time(0));// 这个加上有可能直接RE, 慎重.
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
		remove(root[tid], x);
	}
};
template<typename tp, size_t dsn, size_t pon>
typename treap<tp, dsn, pon>::node *treap<tp, dsn, pon>::node::null;

#endif
