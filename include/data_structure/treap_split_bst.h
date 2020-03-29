#ifndef TREAP_SPLIT_BST_H
#define TREAP_SPLIT_BST_H 1

#include "data_structure/bst.h"

/*
 * treap, split_merge, bst.
 * 优先级用系统的rand.
 * 这里是大顶堆, merge的时候都会判断堆的性质, 需要改的话找merge函数.
 */
template<typename tp, size_t dsn, size_t pon>
class treap : public bst<tp> {
#define link(u, d, v) ((u->ch[d] = v)->fa = u)
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
	pair<node *, node *> split_by_val(node *t, tp x) {
		node *lo = null, *ro = null;
		if (t != null) {
			if (t->key <= x) {// note: <=.
				tie(lo, ro) = split_by_val((node *)t->ch[1], x);
				lo = (node *)link(t, 1, lo)->pull();
			} else {
				tie(lo, ro) = split_by_val((node *)t->ch[0], x);
				ro = (node *)link(t, 0, ro)->pull();
			}
		}
		return {lo, ro};
	}
	node *merge(node *lo, node *ro) {
		node *ret;
		if (lo == null || ro == null) {
			ret = lo == null ? ro : lo;
		} else {
			if (lo->fix > ro->fix) {// heap.
				ro = merge((node *)lo->ch[1], ro);
				ret = (node *)link(lo, 1, ro)->pull();
			} else {
				lo = merge(lo, (node *)ro->ch[0]);
				ret = (node *)link(ro, 0, lo)->pull();
			}
		}
		return ret;
	}
	template<typename ...var>
	node *merge(node *t, var ...args) {
		initializer_list<int>{(t = merge(t, args), 0)...};
		return t;
	}
	void segment(node *&t, tp l, tp r, node *&lo, node *&mo, node *&ro) {
		pair<node *, node *> fd;
		fd = split_by_val(t, r);
		ro = fd.second;
		fd = split_by_val(fd.first, l - 1);
		lo = fd.first;
		mo = fd.second;
	}
	void insert(node *&t, tp x) {
		node *lo, *ro;
		tie(lo, ro) = split_by_val(t, x);
		t = merge(lo, new (alloc()) node(x), ro);
	}
	void remove(node *&t, tp x) {
		node *lo, *mo, *ro;
		segment(t, x, x, lo, mo, ro);
		alloc(mo);
		t = merge(lo, (node *)mo->ls, (node *)mo->rs, ro);
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
#undef link
};
template<typename tp, size_t dsn, size_t pon>
typename treap<tp, dsn, pon>::node *treap<tp, dsn, pon>::node::null;

#endif
