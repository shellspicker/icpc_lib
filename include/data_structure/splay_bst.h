#ifndef SPLAY_BST_H
#define SPLAY_BST_H 1

#include "data_structure/bst.h"

/*
 * splay, bst.
 * 有top_down和down_top的实现方式.
 * 常见的是down_top的实现, 在lct也是这样.
 * top_down的实现, 连接的细节稍微复杂.
 * 旋转如果是自底向上的方式, 可以不用引用.
 * 目前没有push.
 * down_top的push, 需要一个栈.
 * top_down的push可能是往下走的时候直接push, 暂时不研究.
 */
template<typename tp, size_t dsn, size_t pon>
class splay : public bst<tp> {
#define link(u, d, v) ((u->ch[d] = v)->fa = u)
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
		auto helper = [](node *t, int d) {
			node *k = (node *)t->ch[d], *ac = (node *)t->fa;
			link(t, d, k->ch[d ^ 1])->pull();
			link(k, d ^ 1, t);
			link(ac, ac->rs == t, k);
			return k;
		};
		t = helper(t, d);
	}
	void down_top_helper(node *&t, node *x) {
#define get(u, v, d) u = (node *)v->fa, d = u->rs == v
		node *y, *z, *ac = (node *)t->fa;
		bool dy, dz;
		while (x->fa != ac) {
			get(y, x, dy);
			get(z, y, dz);
			if (z != ac && dz == dy)
				rotate(z, dz);
			rotate(y, dy);
		}
		x->pull();
		if (x->fa == ac)
			t = x;
#undef get
	}
	void down_top_by_val(node *&t, tp x) {
		node *o = t;
		if (t == null)
			return;
		o = (node *)bst<tp>::search(o, x, 0, 1, 1).second;
		// push on this.
		down_top_helper(t, o);
	}
	void down_top_by_size(node *&t, int k) {
		node *o = t;
		if (t == null)
			return;
		o = (node *)bst<tp>::kth(o, k, 0);
		// push on this.
		down_top_helper(t, o);
	}
	void top_down_by_val(node *&t, tp x) {
		node *o = t, *fa = (node *)t->fa, *lr[2] = {null, null};
		if (o == null)
			return;
		while (o->key != x) {
			bool d = o->key < x;
			if (o->ch[d] == null)
				break;
			if (o->ch[d]->ch[d] != null) {
				tp dk = o->ch[d]->key;
				if ((!d && x <= dk) || (d && dk <= x)) {
					rotate(o, d);
					if (o->key == x)
						break;
				}
			}
			link(lr[d], d, o);
			lr[d] = (node *)lr[d]->ch[d];
			o = (node *)o->ch[d];
		}
		fup (d, 0, 1) {
			node *cur = (node *)link(lr[d], d, o->ch[d ^ 1]);
			while (cur != null)
				cur = (node *)cur->pull()->fa;
		}
		link(o, 0, null->ch[1]);
		link(o, 1, null->ch[0]);
		(t = o)->pull()->fa = fa;
	}
	void top_down_by_size(node *&t, int k) {
		node *o = t, *fa = (node *)t->fa, *lr[2] = {null, null};
		if (o == null)
			return;
		while (o != null) {
			int s = o->ls->size + 1;
			if (k == s)
				break;
			bool d = s < k;
			if (o->ch[d]->ch[d] != null) {
				int ss = o->ch[d]->ls->size + 1;
				if (((!d && k <= ss) || (d && ss <= k - s))) {
					rotate(o, d);
					s = o->ls->size + 1;
					if (k == s)
						break;
				}
			}
			link(lr[d], d, o);
			lr[d] = (node *)lr[d]->ch[d];
			o = (node *)o->ch[d];
			if (d)
				k -= s;
		}
		fup (d, 0, 1) {
			node *cur = (node *)link(lr[d], d, o->ch[d ^ 1]);
			while (cur != null)
				cur = (node *)cur->pull()->fa;
		}
		link(o, 0, null->ch[1]);
		link(o, 1, null->ch[0]);
		(t = o)->pull()->fa = fa;
	}
	node *insert(node *&t, tp x) {
		if (t == null) {
			t = new (alloc()) node(x);
		} else {
			bool d = t->key < x;// equal or not is don't care.
			insert((node *&)t->ch[d], x)->fa = t;
			t->pull();
		}
		return t;
	}
	void insert_top_down(node *&t, tp x) {
		node *o = new (alloc()) node(x);
		if (t == null) {
			t = o;
		} else {
			top_down_by_val(t, x);
			bool d = t->key < x;// equal or not is don't care.
			link(o, d, t->ch[d]);
			t->ch[d] = null;
			t = (node *)link(o, d ^ 1, t->pull());
		}
		t->pull()->fa = null;
	}
	void remove(node *&t, tp x) {
		down_top_by_val(t, x);
		if (t->key ^ x)
			return;
		alloc(t);
		if (t->ls == null || t->rs == null) {
			t = t->ls == null ? (node *)t->rs : (node *)t->ls;
		} else {
			bool d = t->ls->size > t->rs->size;
			down_top_by_val((node *&)t->ch[d], t->key + (d ? -1 : 1));
			//down_top_by_size((node *&)t->ch[d], !d ? t->ch[d]->size : 1);
			t = (node *)link(t->ch[d], d ^ 1, t->ch[d ^ 1]);
		}
		t->fa = null;
		if (t != null)
			t->pull();
	}
	void remove_top_down(node *&t, tp x) {
		top_down_by_val(t, x);
		if (t->key != x)
			return;
		alloc(t);
		if (t->ls == null || t->rs == null) {
			t = t->ls == null ? (node *)t->rs : (node *)t->ls;
		} else {
			bool d = t->ls->size > t->rs->size;
			top_down_by_val((node *&)t->ch[d], t->key + (!d ? 1 : -1));
			//top_down_by_size((node *&)t->ch[d], !d ? t->ch[d]->size : 1);
			t = (node *)link(t->ch[d], d ^ 1, t->ch[d ^ 1]);
		}
		t->fa = null;
		if (t != null)
			t->pull();
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
		balance(tid, x);
	}
	void remove(int tid, tp x) {
		remove(root[tid], x);
		balance(tid, x);
	}
	void balance(int tid, tp x) {
		down_top_by_val(root[tid], x);
		//top_down_by_val(root[tid], x);
	}
#undef link
};
template<typename tp, size_t dsn, size_t pon>
typename splay<tp, dsn, pon>::node *splay<tp, dsn, pon>::node::null;

#endif
