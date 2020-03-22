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
private:
	class node : public bst<tp>::node {
	public:
		static node *null;
		int fix;
		// 附加信息
		//int val;// map用, 对应看map版本的insert里面.
		node() {}
		node(node *f, tp k) : bst<tp>::node(f, k) {
			fix = rand();
		}
	};
	allocator<node, pon> alloc;
public:
	node *&null = node::null;// null must be reference.
	node *root[dsn];
	void init() {
		srand(time(0));// 这个加上有可能直接RE, 慎重.
		alloc.clear();
		null = new (alloc()) node(null, -1);
		bst<tp>::null = null;
		null->size = 0;
		fup (i, 0, dsn - 1)
			root[i] = null;
	}
	node *&operator ()(int idx) {
		return root[idx];
	}
	node *link(node *fa, node *son) {
		son->fa = fa;
		return fa;
	}
	pair<node *, node *> split(node *o, tp x) {
		if (o == null)
			return {null, null};
		node *lo, *ro;
		if (o->key <= x) {// note: <=.
			tie(lo, ro) = split((node *)o->rs, x);
			return {(node *)link(o, (node *)(o->rs = lo))->pull(), ro};
		} else {
			tie(lo, ro) = split((node *)o->ls, x);
			return {lo, (node *)link(o, (node *)(o->ls = ro))->pull()};
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
	node *insert(node *&o, int x) {
		node *lo, *ro;
		tie(lo, ro) = split(o, x);
		o = merge(merge(lo, new (alloc()) node(null, x)), ro);
		return o;
	}
	node *remove(node *&o, int x) {
		node *lo, *mo, *ro;
		tie(lo, mo) = split(o, x - 1);
		tie(mo, ro) = split(mo, x);
		alloc(mo);
		o = merge(merge(lo, merge((node *)mo->ls, (node *)mo->rs)), ro);
		return o;
	}
};
template<typename tp, size_t dsn, size_t pon>
typename treap<tp, dsn, pon>::node *treap<tp, dsn, pon>::node::null;

#endif
