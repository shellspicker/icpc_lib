#pragma once

#ifndef SELECT_MODE
#define SELECT_MODE TOP_DOWN
#endif
#define TOP_DOWN 0
#define DOWN_TOP 1

#if SELECT_MODE == DOWN_TOP
#define FATHER 1
#endif

#include "data_structure/bst.h"

/*
 * splay.
 * 宏: SELECT_MODE(TOP_DOWN, DOWN_TOP), (FUNC_RANGE, FUNC_BST), FATHER.
 *
 * FUNC_RANGE.
 * 区间树.
 * 设置FATHER选择是否需要父结点.
 *
 * FUNC_BST.
 * 平衡树.
 * NOTE: 查找完后需要手动调用select_by_val, 把操作点转上来.
 *
 * SELECT_MODE.
 * 选择旋转方式, 自顶向下or自底向上, 默认自顶向下, 操作更快.
 *
 * 旋转方式.
 * 有top_down和down_top的实现方式.
 * 常见的是down_top的实现, 在lct也是这样.
 * 如果是down_top的方式, 可以不用引用.
 *
 * top_down的实现.
 * 连接的细节稍微复杂, 注意切断的实现(父结点也要切断, 体现为连接null和当前点).
 * 这里的实现, 和网上博客说的辅助树连接过程是相反的, 类似一个栈, 网上说的是队列.
 * 合并辅助树的时候再弹出栈就行, 这样还是原来的顺序.
 * 这里用非递归实现, 当然也可以考虑递归实现(细节类似down_top).
 */
template<typename tp, size_t dsn, size_t pon>
class splay : public bst<tp> {
#define ls ch[0]
#define rs ch[1]
#if FATHER
#define link(u, d, v) ((u->ch[d] = v)->fa = u)
#else
#define link(u, d, v) ((u->ch[d] = v), u)
#endif
	class node : public bst<tp>::node {
	public:
		static node *null;
		// 附加信息
		//int val;// map用.
#if FUNC_RANGE
		bool rev;
#endif
		node() {}
		node(tp k) : bst<tp>::node(k) {
#if FUNC_RANGE
			rev = 0;
#endif
		}
#if FUNC_RANGE
		void release() {
			if (this == null)
				return;
			swap(this->ls, this->rs);
			rev ^= 1;
		}
		void push() {
			if (rev) {
				((node *)this->ls)->release();
				((node *)this->rs)->release();
				rev = 0;
			}
		}
#endif
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
#if SELECT_MODE == TOP_DOWN
	void select_by_val(node *&t, tp x) {
#define magic_go(master, d, other)\
		go = (node *)master->ch[d];\
		other = (node *)link(master, d, other);\
		master = go
		node *o = t, *lr[2] = {null, null}, *go;
#if FATHER
		node *fa = (node *)t->fa;
#endif
		if (o == null)
			return;
		while (o->key != x) {
			bool d = o->key < x;
			if (o->ch[d] == null)
				break;
			if (o->ch[d]->ch[d] != null) {
				tp dk = o->ch[d]->key;
				if ((!d && x < dk) || (d && dk < x)) {
					rotate(o, d);
					if (o->key == x)
						break;
				}
			}
			magic_go(o, d, lr[d]);
#if FATHER
			link(null, d, o);
#endif
		}
		fup (d, 0, 1) {
			while (lr[d] != null) {
				magic_go(lr[d], d, o->ch[d ^ 1]);
				o->ch[d ^ 1]->pull();
			}
#if FATHER
			link(o, d ^ 1, o->ch[d ^ 1]);
#endif
		}
		(t = o)->pull();
#if FATHER
		t->fa = fa;
#endif
#undef magic_go
	}
	void select_by_size(node *&t, int k) {
#define finded()\
		o->push();\
		s = o->ls->size + 1;\
		if (k == s)\
			break
#define magic_go(master, d, other)\
		go = (node *)master->ch[d];\
		other = (node *)link(master, d, other);\
		master = go
		node *o = t, *lr[2] = {null, null}, *go;
#if FATHER
		node *fa = (node *)t->fa;
#endif
		int s;
		if (o == null)
			return;
		while (o != null) {
			finded();
			bool d = s < k;
			((node *)o->ch[d])->push();
			int ss = o->ch[d]->ls->size + 1;
			if (((!d && k < ss) || (d && ss < k - s))) {
				rotate(o, d);
				finded();
			}
			magic_go(o, d, lr[d]);
#if FATHER
			link(null, d, o);
#endif
			if (d)
				k -= s;
		}
		fup (d, 0, 1) {
			while (lr[d] != null) {
				magic_go(lr[d], d, o->ch[d ^ 1]);
				o->ch[d ^ 1]->pull();
			}
#if FATHER
			link(o, d ^ 1, o->ch[d ^ 1]);
#endif
		}
		(t = o)->pull();
#if FATHER
		t->fa = fa;
#endif
#undef finded
#undef magic_go
	}
#endif
#if SELECT_MODE == DOWN_TOP
	void select_node(node *&t, node *x) {
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
	void select_by_val(node *&t, tp x) {
		node *o = t;
		if (t == null)
			return;
		o = (node *)bst<tp>::search(o, x, 0, 1, 1).second;
		// push on this.
		select_node(t, o);
	}
	void select_by_size(node *&t, int k) {
		node *cur, *o = t, *fa = (node *)t->fa;
		if (t == null)
			return;
		while (o != null) {
#if FUNC_RANGE
			o->push();
#endif
			int s = o->ls->size + 1;
			if (s == k)
				break;
			bool d = s < k;
			o = (node *)o->ch[d];
			if (d)
				k -= s;
		}
		select_node(t, o);
	}
#endif
#if FUNC_RANGE
	node *build(node *&t, vector<tp> &v, int l, int r) {
		if (!length(l, r))
			return null;
		int mid = midpoint(l, r);
		t = new (alloc()) node(v[mid]);
#if FATHER
		build((node *&)t->ls, v, l, mid - 1)->fa = t;
		build((node *&)t->rs, v, mid + 1, r)->fa = t;
#else
		build((node *&)t->ls, v, l, mid - 1);
		build((node *&)t->rs, v, mid + 1, r);
#endif
		t->pull();
		return t;
	}
	node *&segment(node *&t, int l, int r) {
		l++, r++;
		select_by_size(t, r + 1);
		select_by_size((node *&)t->ls, l - 1);
		return (node *&)t->ls->rs;
	}
	void visit(node *o, vector<tp> &out) {
		if (o == null)
			return;
		o->push();
		visit((node *)o->ls, out);
		out.emplace_back(o->key);
		visit((node *)o->rs, out);
	}
#endif
#if FUNC_BST
	void insert(node *&t, tp x) {
		node *o = new (alloc()) node(x);
		if (t == null) {
			t = o;
		} else {
			select_by_val(t, x);
			bool d = t->key < x;// equal or not is don't care.
			link(o, d, t->ch[d]);
			t->ch[d] = null;
			t = (node *)link(o, d ^ 1, t->pull());
		}
		t->pull();
#if FATHER
		t->fa = null;
#endif
	}
	void remove(node *&t, tp x) {
		select_by_val(t, x);
		if (t->key ^ x)
			return;
		alloc(t);
		if (t->ls == null || t->rs == null) {
			t = t->ls == null ? (node *)t->rs : (node *)t->ls;
		} else {
			bool d = t->ls->size > t->rs->size;
			select_by_val((node *&)t->ch[d], t->key + (d ? -1 : 1));
			t = (node *)link(t->ch[d], d ^ 1, t->ch[d ^ 1]);
		}
		if (t != null)
			t->pull();
#if FATHER
		t->fa = null;
#endif
	}
#endif
public:
	node *root[dsn], *&null = node::null;// null must be reference.
#if FUNC_RANGE
	node *nos[dsn][2];
#endif
	void init() {
		alloc.clear();
		null = new (alloc()) node(-1);
		bst<tp>::null = null;
		null->size = 0;
		null->ls = null->rs = null;
		fup (i, 0, dsn - 1) {
#if FUNC_RANGE
			nos[i][0] = new (alloc()) node(-inf32);
			nos[i][1] = new (alloc()) node(inf32);
			root[i] = (node *)link(nos[i][0], 1, nos[i][1])->pull();
#endif
#if FUNC_BST
			root[i] = null;
#endif
		}
	}
	node *&operator ()(int idx) {
		return root[idx];
	}
#if FUNC_RANGE
	void build(int tid, vector<tp> &v) {
		node *&t = root[tid], *&sub = segment(t, 1, t->size - 2);
#if FATHER
		build(sub, v, 0, v.size() - 1)->fa = t->ls;
#else
		build(sub, v, 0, v.size() - 1);
#endif
		t->ls->pull();
		t->pull();
	}
	void reverse(int tid, int l, int r) {
		node *&t = root[tid], *&sub = segment(t, l, r);
		sub->release();
		t->ls->pull();
		t->pull();
	}
	void print(int tid, vector<tp> &out) {
		out.clear();
		visit(segment(root[tid], 1, root[tid]->size - 2), out);
	}
#endif
#if FUNC_BST
	void insert(int tid, tp x) {
		insert(root[tid], x);
	}
	void remove(int tid, tp x) {
		remove(root[tid], x);
	}
	void select_by_val(int tid, tp x) {
		select_by_val(root[tid], x);
	}
#endif
#undef ls
#undef rs
#undef link
};
template<typename tp, size_t dsn, size_t pon>
typename splay<tp, dsn, pon>::node *splay<tp, dsn, pon>::node::null;

#undef SELECT_MODE
#undef TOP_DOWN
#undef DOWN_TOP
#undef FATHER
#undef FUNC_RANGE
#undef FUNC_BST
