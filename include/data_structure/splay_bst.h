#ifndef SPLAY_BST_H
#define SPLAY_BST_H 1

#include "data_structure/bst.h"

/*
 * splay, bst.
 * 旋转和treap的不太一样, 因为这里是从下往上转, 所以要手动连接一下ac结点.
 * 之后考虑这里修改一下.
 * go函数可以加push, 需要一个栈.
 */
template<typename tp, size_t dsn, size_t pon>
class splay : public bst<tp> {
private:
	static constexpr double alpha = 0.75;
	class node : public bst<tp>::node {
	public:
		static node *null;
		using bst<tp>::node::ls;
		using bst<tp>::node::rs;
		using bst<tp>::node::size;
		// 附加信息
		//int val;// map用, 对应看map版本的insert里面.
		node() {}
		node(node *f, tp k) : bst<tp>::node(f, k) {}
		bool bad() {
			return (size * alpha + 5 < ls->size)
				|| (size * alpha + 5 < rs->size);
		}
	};
	allocator<node, pon> alloc;
public:
	node *root[dsn], *&null = node::null;// null must be reference.
	void init() {
		alloc.clear();
		null = new (alloc()) node(null, -1);
		bst<tp>::null = null;
		null->size = 0;
		null->ls = null->rs = null;
		fup (i, 0, dsn - 1)
			root[i] = null;
	}
	node *&operator ()(int idx) {
		return root[idx];
	}
	// d方向的子结点旋转上来.
	void rotate(node *&o, int d) {
		auto helper = [](node *o, int d) {
#define link(u, d, v) ((u->ch[d] = v)->fa = u)
			node *k = (node *)o->ch[d], *ac = (node *)o->fa;
			link(o, d, k->ch[d ^ 1])->pull();
			link(k, d ^ 1, o);
			link(ac, ac->rs == o, k);
			return k;
#undef link
		};
		o = helper(o, d);
	}
	void play(node *&t, node *x, node *goal) {
#define get(u, v, d) u = (node *)v->fa, d = u->rs == v
		node *y, *z;
		bool dy, dz;
		while (x->fa != goal) {
			get(y, x, dy);
			if (y->fa != goal) {
				get(z, y, dz);
				if (dz == dy)
					rotate(z, dz);
			}
			rotate(y, dy);
		}
		x->pull();
		if (x->fa == null)
			t = x;
#undef get
	}
	void go(node *&t, int k, node *goal) {
		node *o = t;
		o = (node *)bst<tp>::kth(o, k, 0);
		// push on this.
		play(t, o, goal);
	}
	node **insert(node *&o, node *f, tp x) {
		node **ret;
		if (o == null) {
			o = new (alloc()) node(!f ? null : f, x);
			ret = &null;
		} else {
			bool d = o->key < x;// equal or not is don't care.
			ret = insert((node *&)o->ch[d], o, x);
			o->pull();
			if (o->bad())
				ret = &o;
		}
		return ret;
	}
	void insert(node *&t, tp x) {
		node **fix = insert(t, 0, x);
		if (*fix != null)
			go(*fix, ((*fix)->size + 1) >> 1, (node *)(*fix)->fa);
	}
	bool remove(node *&o, tp x) {
		auto fd = bst<tp>::search(o, x, 0, 1);
		if (fd.second->key ^ x)
			return 0;
		play(o, (node *)fd.second, null);
		if (fd.first == 1) {
			alloc(o);
			(o = (node *)o->rs)->fa = null;
		} else {
			go(o, fd.first - 1, o);
			alloc(o);
			(o = (node *)((o->ls->rs = o->rs)->fa = o->ls))->fa = null;
		}
		if (o != null)
			o->pull();
		if (o->bad())
			go(o, (o->size + 1) >> 1, null);
		return 1;
	}
};
template<typename tp, size_t dsn, size_t pon>
typename splay<tp, dsn, pon>::node *splay<tp, dsn, pon>::node::null;

#endif
