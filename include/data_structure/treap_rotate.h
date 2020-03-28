#ifndef TREAP_ROTATE_H
#define TREAP_ROTATE_H 1

#include "data_structure/bst.h"

/*
 * treap, rotate.
 * 优先级用系统的rand.
 * 这里是大顶堆, rotate之前都会判断堆的性质, 需要改的话找调用rotate的地方.
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
	// d方向的子结点旋转上来.
	void rotate(node *&t, int d) {
		auto helper = [](node *t, int d) {
			node *k = (node *)t->ch[d], *ac = (node *)t->fa;
			link(t, d, k->ch[d ^ 1])->pull();
			link(k, d ^ 1, t);
			k->fa = ac;
			return k;
		};
		t = helper(t, d);
	}
	// multiset
	node *insert(node *&t, tp x) {
		if (t == null) {
			t = new (alloc()) node(x);
		} else {
			bool d = t->key < x;// equal or not is don't care.
			insert((node *&)t->ch[d], x)->fa = t;
			if (((node *)t->ch[d])->fix > t->fix)// heap.
				rotate(t, d);
			t->pull();
		}
		return t;
	}
	// 有判断删除值存在
	bool remove(node *&t, tp x) {
		if (t == null)
			return 0;
		bool ok;
		if (x == t->key) {
			if (t->ls == null || t->rs == null) {
				node *fa = (node *)t->fa;
				alloc(t);
				(t = t->ls != null ? (node *)t->ls : (node *)t->rs)->fa = fa;
				ok = 1;
			} else {
				int d = (((node *)t->ls)->fix > ((node *)t->rs)->fix ? 0 : 1);// heap.
				rotate(t, d);
				ok = remove((node *&)t->ch[d ^ 1], x);
			}
		} else {
			ok = remove((node *&)t->ch[t->key < x], x);
		}
		if (t != null)
			t->pull();
		return ok;
	}
public:
	node *root[dsn], *&null = node::null;// null must be reference.
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
