#ifndef SPLAY_RANGE_H
#define SPLAY_RANGE_H 1

#include "data_structure/bst.h"

/*
 * splay, range.
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
		using bst<tp>::node::ls;
		using bst<tp>::node::rs;
		static node *null;
		// 附加信息
		//int val;// map用.
		bool rev;
		node() {}
		node(tp k) : bst<tp>::node(k) { rev = 0; }
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
	void down_top_by_size(node *&t, int k) {
		stack<node *> st;
		node *cur, *o = t, *fa = (node *)t->fa;
		if (t == null)
			return;
		while (o != null) {
			o->push();
			int s = o->ls->size + 1;
			if (s == k)
				break;
			bool d = s < k;
			o = (node *)o->ch[d];
			if (d)
				k -= s;
		}
		down_top_helper(t, o);
	}
	node *build(node *&t, vector<tp> &v, int l, int r) {
		if (!length(l, r))
			return null;
		int mid = midpoint(l, r);
		t = new (alloc()) node(v[mid]);
		build((node *&)t->ls, v, l, mid - 1)->fa = t;
		build((node *&)t->rs, v, mid + 1, r)->fa = t;
		t->pull();
		return t;
	}
	node *&segment(node *&t, int l, int r) {
		l++, r++;
		down_top_by_size(t, r + 1);
		down_top_by_size((node *&)t->ls, l - 1);
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
public:
	node *root[dsn], *nos[dsn][2], *&null = node::null;// null must be reference.
	void init() {
		alloc.clear();
		null = new (alloc()) node(-1);
		bst<tp>::null = null;
		null->size = 0;
		null->ls = null->rs = null;
		fup (i, 0, dsn - 1) {
			nos[i][0] = new (alloc()) node(-inf32);
			nos[i][1] = new (alloc()) node(inf32);
			root[i] = (node *)link(nos[i][0], 1, nos[i][1])->pull();
		}
	}
	node *&operator ()(int idx) {
		return root[idx];
	}
	void reverse(int tid, int l, int r) {
		node *&t = root[tid], *&sub = segment(t, l, r);
		sub->release();
		t->ls->pull();
		t->pull();
	}
	void build(int tid, vector<tp> &v) {
		node *&t = root[tid], *&sub = segment(t, 1, t->size - 2);
		build(sub, v, 0, v.size() - 1)->fa = t->ls;
		t->ls->pull();
		t->pull();
	}
	void print(int tid, vector<tp> &out) {
		out.clear();
		visit(segment(root[tid], 1, root[tid]->size - 2), out);
	}
#undef link
};
template<typename tp, size_t dsn, size_t pon>
typename splay<tp, dsn, pon>::node *splay<tp, dsn, pon>::node::null;

#endif
