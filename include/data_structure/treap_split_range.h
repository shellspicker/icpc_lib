#ifndef TREAP_SPLIT_RANGE_H
#define TREAP_SPLIT_RANGE_H 1

#include "data_structure/bst.h"

/*
 * treap, split_merge, range.
 * 优先级用系统的rand.
 * 这里是大顶堆, merge的时候都会判断堆的性质, 需要改的话找merge函数.
 */
template<typename tp, size_t dsn, size_t pon>
class treap : public bst<tp> {
#define link(u, d, v) ((u->ch[d] = v)->fa = u)
	class node : public bst<tp>::node {
	public:
		using bst<tp>::node::ls;
		using bst<tp>::node::rs;
		static node *null;
		int fix;
		// 附加信息
		//int val;// map用.
		bool rev;
		node() {}
		node(tp k) : bst<tp>::node(k) {
			fix = rand();
			rev = 0;
		}
		void release() {
			if (this == null)
				return;
			swap(ls, rs);
			rev ^= 1;
		}
		void push() {
			if (rev) {
				((node *)ls)->release();
				((node *)rs)->release();
				rev = 0;
			}
		}
	};
	allocator<node, pon> alloc;
	pair<node *, node *> split_by_size(node *t, int k) {
		node *lo = null, *ro = null;
		if (t != null) {
			t->push();
			int s = t->ls->size + 1;
			if (s <= k) {// note: <=.
				tie(lo, ro) = split_by_size((node *)t->ch[1], k - s);
				lo = (node *)link(t, 1, lo)->pull();
			} else {
				tie(lo, ro) = split_by_size((node *)t->ch[0], k);
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
				lo->push();
				ro = merge((node *)lo->ch[1], ro);
				ret = (node *)link(lo, 1, ro)->pull();
			} else {
				ro->push();
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
	void segment(node *&t, int l, int r, node *&lo, node *&mo, node *&ro) {
		pair<node *, node *> fd;
		fd = split_by_size(t, r);
		ro = fd.second;
		fd = split_by_size(fd.first, l - 1);
		lo = fd.first;
		mo = fd.second;
	}
	void build(node *&t, vector<tp> &v) {
		node *last = null;
		for (auto x : v) {
			node *o = new (alloc()) node(x);
			while (last != null && o->fix > last->fix)
				last = (node *)last->pull()->fa;
			node *fix = (node *)last->rs;
			link(o, 0, fix)->pull();
			link(last, 1, o);
			last = o;
			if (o->fa == null)
				t = o;
		}
		while (last != null)
			last = (node *)last->pull()->fa;
	}
	void reverse(node *&t, int l, int r) {
		node *lo, *mo, *ro;
		segment(t, l, r, lo, mo, ro);
		mo->release();
		t = merge(lo, mo, ro);
	}
	void visit(node *o, vector<tp> &out) {
		if (o == null)
			return;
		o->push();
		visit((node *)o->ls, out);
		out.emplace_back(o->key);
		visit((node *)o->rs, out);
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
	void build(int tid, vector<tp> &v) {
		build(root[tid], v);
	}
	void reverse(int tid, int l, int r) {
		reverse(root[tid], l, r);
	}
	void print(int tid, vector<tp> &out) {
		out.clear();
		visit(root[tid], out);
	}
#undef link
};
template<typename tp, size_t dsn, size_t pon>
typename treap<tp, dsn, pon>::node *treap<tp, dsn, pon>::node::null;

#endif
