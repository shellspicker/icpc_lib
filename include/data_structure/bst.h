#ifndef BST_H
#define BST_H 1

/*
 * 二叉搜索树.
 * 只有搜索的功能, 其他的由平衡树来继承.
 */
template<typename tp>
class bst {
protected:
	class node {
	public:
		static node *null;
		node *fa, *ch[2], *&ls = ch[0], *&rs = ch[1];
		tp key;
		int size;
		node() {}
		node(node *f, tp k) {
			ls = rs = null;
			fa = f, key = k, size = 1;
		}
		node *pull() {
			size = ls->size + rs->size + 1;
			return this;
		}
	};
	node *&null = node::null;
public:
	/*
	 * 前驱后继, 需要父结点
	 * d: 0为前驱, 1为后继
	 */
	node *order(node *o, bool d) {
		if (o->ch[d] != null) {
			o = o->ch[d];
			while (o->ch[d ^ 1] != null)
				o = o->ch[d ^ 1];
			return o;
		}
		node *last;
		do {
			o = (last = o)->fa;
		} while (o != null && o->ch[d ^ 1] != last);
		return o;
	}
	node *kth(node *o, int k, bool d) {
		if (!inrange(k, 1, o->size))
			return null;
		while (o != null) {
			int s = o->ch[d]->size + 1;
			if (k == s)
				return o;
			bool ok = s < k;
			o = o->ch[ok];
			if (ok)
				k -= s;
		}
		return null;
	}
	/*
	 * 二分系列其实平衡树只能找到[)端点, 因为只能向下走,
	 * 最后端点都会往右边超界.
	 * 如果返回排名的话, 对应ans得到的是[), ans-1得到的是(].
	 * 类似的还有直接返回对应结点, so, 能返回的信息有<rank, node*>.
	 * 参数和原理类比数组版本的二分.
	 */
	pair<int, node *> search(node *o, tp x, bool d, bool contain) {
#define dwn(cond) \
		if ((cond)) ans += o->ls->size + 1, o = o->ch[lastdir = 1];\
		else o = o->ch[lastdir = 0]
		int ans = 1;// 从1开始标号.
		node *last = null;
		bool lastdir;
		while (o != null) {
			last = o;
			dwn((d == 0 && o->key < x) || (d == 1 && !(x < o->key)));
		}
		ans = d ^ contain ? ans : ans - 1;
		o = d ^ contain ^ lastdir ? last : order(last, lastdir);
		return {ans, o};
#undef dwn
	}
};
template<typename tp>
typename bst<tp>::node *bst<tp>::node::null;

#endif
