#ifndef SBT_H
#define SBT_H 1

#include "data_structure/bst.h"

/*
 * sbt.
 * 详细参考陈启锋论文"Size Balanced Tree".
 * 核心思想在于maintain和remove.
 */
template<typename tp, size_t dsn, size_t pon>
class sbt : public bst<tp> {
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
	void maintain(node *&o, int d)
	{
		if (o->ch[d] == null)
			goto end;
		if (o->ch[d ^ 1]->size < o->ch[d]->ch[d]->size) {
			rotate(o, d);
		} else if(o->ch[d ^ 1]->size < o->ch[d]->ch[d ^ 1]->size) {
			rotate((node *&)o->ch[d], d ^ 1);
			rotate(o, d);
		} else {
			goto end;
		}
		maintain((node *&)o->ch[d], d);
		maintain((node *&)o->ch[d ^ 1],d ^ 1);
		maintain(o, 0);
		maintain(o, 1);
end:
		o->pull();
	}
	void insert(node *&o, node *f, tp x)
	{
		if (o==null) {
			o = new (alloc()) node(!f ? null : f, x);
		} else {
			bool d = o->key < x;// equal or not is don't care.
			insert((node *&)o->ch[d], o, x);
			maintain(o, d);
		}
	}
	tp remove(node *&o, tp x)// 返回删除的值, 删除的值可以不在树里面.
	{
		if (o == null)
			return 0;
		int ret;
		/*
		 * case1: 找到合适的1个点.
		 * case2: 还在查找的途中.
		 */
		if (x == o->key || (x < o->key && o->ls == null) || (o->key < x && o->rs == null)) {
			// case1.
			ret = o->key;// 此点必定被删除
			if(o->ls == null || o->rs == null) {// 对应后面2个条件, 不一定删除的是准确值?
				alloc(o);
				node *tmp = o->ls != null? (node *)o->ls: (node *)o->rs;
				tmp->fa = o->fa;
				o = tmp;
			} else {
				// 替换成子树中最接近当前结点的值.
				if (o->ls->size < o->rs->size)
					o->key = remove((node *&)o->ls, o->key + 1);
				else
					o->key = remove((node *&)o->rs, o->key - 1);
			}
		} else {
			// case2:
			ret = remove((node *&)o->ch[o->key < x], x);
		}
		if (o != null)
			o->pull();
		return ret;
	}
};
template<typename tp, size_t dsn, size_t pon>
typename sbt<tp, dsn, pon>::node *sbt<tp, dsn, pon>::node::null;

#endif
