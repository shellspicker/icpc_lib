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
	node *root[dsn], *&null = node::null;// null must be reference.
	void init() {
		srand(time(0));// 这个加上有可能直接RE, 慎重.
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
			k->fa = ac;
			return k;
#undef link
		};
		o = helper(o, d);
	}
	// multiset
	void insert(node *&o, node *f, tp x) {
		if (o == null) {
			o = new (alloc()) node(!f ? null : f, x);
		} else {
			bool d = o->key < x;// equal or not is don't care.
			insert((node *&)o->ch[d], o, x);
			if (((node *)o->ch[d])->fix > o->fix)// heap.
				rotate(o, d);
			o->pull();
		}
	}
	// 有判断删除值存在
	bool remove(node *&o, tp x) {
		if (o == null)
			return 0;
		bool ok;
		if (x == o->key) {
			if (o->ls == null || o->rs == null) {
				node *fa = (node *)o->fa;
				alloc(o);
				(o = o->ls != null ? (node *)o->ls : (node *)o->rs)->fa = fa;
				ok = 1;
			} else {
				int d = (((node *)o->ls)->fix > ((node *)o->rs)->fix ? 0 : 1);// heap.
				rotate(o, d);
				ok = remove((node *&)o->ch[d ^ 1], x);
			}
		} else {
			ok = remove((node *&)o->ch[o->key < x], x);
		}
		if (o != null)
			o->pull();
		return ok;
	}
};
template<typename tp, size_t dsn, size_t pon>
typename treap<tp, dsn, pon>::node *treap<tp, dsn, pon>::node::null;

#endif
