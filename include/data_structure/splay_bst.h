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
	class node : public bst<tp>::node {
	public:
		static node *null;
		// 附加信息
		//int val;// map用, 对应看map版本的insert里面.
		node() {}
		node(node *f, tp k) : bst<tp>::node(f, k) {}
	};
	allocator<node, pon> alloc;
public:
	node *root[dsn], *&null = node::null;// null must be reference.
	void init() {
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
	node *rotate(node *&o, int d) {
		auto link = [](node *u, int d, node *v) {
			return (u->ch[d] = v)->fa = u;
		};
		node *k = (node *)o->ch[d], *ac = (node *)o->fa;
		link(o, d, (node *)k->ch[d ^ 1])->pull();
		ac->ch[ac->rs == o] = k;// 其他从上到下的树, 这里左值就是o, 这里不是.
		link(k, d ^ 1, o);
		(o = k)->fa = ac;
		return o;
	}
	void play(node *&t, node *x, node *goal) {
		node *y, *z;
		while (x->fa != goal) {
			y = (node *)x->fa;
			if (y->fa == goal) {
				rotate(y, y->rs == x);
			} else {
				z = (node *)y->fa;
				bool d1 = z->rs == y, d2 = y->rs == x;
				if (d1 ^ d2) {
					rotate(y, d2);
					rotate(z, d1);
				} else {
					rotate(z, d1);
					rotate(y, d2);
				}
			}
		}
		x->pull();
		if (x->fa == null)
			t = x;
	}
	void go(node *&t, int k, node *goal) {
		node *o = t;
		o = (node *)bst<tp>::kth(o, k, 0);
		// push on this.
		play(t, o, goal);
	}
	node *insert(node *&o, node *f, tp x) {
		node *ret;
		if (o == null) {
			ret = o = new (alloc()) node(!f ? null : f, x);
		} else {
			bool d = o->key < x;// equal or not is don't care.
			ret = insert((node *&)o->ch[d], o, x);
			o->pull();
		}
		return ret;
	}
	bool remove(node *&o, tp x) {
		auto fd = bst<tp>::search(o, x, 0, 1);
		if (fd.second->key ^ x)
			return 0;
		play(o, (node *)fd.second, null);
		if (fd.first == 1) {
			alloc(o);
			(o = (node *)o->rs)->fa = null;
			o->pull();
		} else {
			go(o, fd.first - 1, o);
			alloc(o);
			(o = (node *)((o->ls->rs = o->rs)->fa = o->ls))->fa = null;
			o->pull();
		}
		return 1;
	}
};
template<typename tp, size_t dsn, size_t pon>
typename splay<tp, dsn, pon>::node *splay<tp, dsn, pon>::node::null;

#endif
