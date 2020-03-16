#ifndef TREAP_SPLIT_H
#define TREAP_SPLIT_H 1

/*
 * treap, split_merge版本.
 * 优先级用系统的rand.
 * 这里是大顶堆, merge的时候都会判断堆的性质, 需要改的话找merge函数.
 * 可模拟set, map, multiset.
 * 几个二分相关的查找函数, 合并了, 方向自己调参数, 0左1右.
 * 模拟map的时候注意, map[key] = val, 这个key要是找不到的话,
 * map里面默认的应该值是0, 这里也要如此判断一下找不到的情况.
 */
template<typename tp, size_t dsn, size_t pon>
class treap {
private:
	class node {
	public:
		static node *null;
		node *fa, *ch[2], *&ls = ch[0], *&rs = ch[1];
		tp key;
		int fix, size;
		// 附加信息
		//int val;// map用, 对应看map版本的insert里面.
		node *assign(node *f, tp k) {
			fa = f, ls = rs = null;
			key = k, fix = rand(), size = 1;
			return this;
		}
		node *pull() {
			size = ls->size + rs->size + 1;
			return this;
		}
	};
	allocator<node, pon> alloc;
public:
	node *root[dsn], *&null = node::null;// null must be reference.
	void init() {
		srand(time(0));// 这个加上有可能直接RE, 慎重.
		alloc.clear();
		null = alloc()->assign(null, -1);
		null->size = 0;
		fup (i, 0, dsn - 1)
			root[i] = null;
	}
	node *&operator ()(int idx) {
		return root[idx];
	}
	node *link(node *fa, node *son) {
		son->fa = fa;
		return fa;
	}
	pair<node *, node *> split(node *o, tp x) {
		if (o == null)
			return {null, null};
		node *lo, *ro;
		if (o->key <= x) {// note: <=.
			tie(lo, ro) = split(o->rs, x);
			return {link(o, o->rs = lo)->pull(), ro};
		} else {
			tie(lo, ro) = split(o->ls, x);
			return {lo, link(o, o->ls = ro)->pull()};
		}
	}
	node *merge(node *lo, node *ro) {
		if (lo == null || ro == null)
			return lo == null ? ro : lo;
		if (lo->fix > ro->fix)// heap.
			return link(lo, lo->rs = merge(lo->rs, ro))->pull();
		else
			return link(ro, ro->ls = merge(lo, ro->ls))->pull();
	}
	node *insert(node *&o, int x) {
		node *lo, *ro;
		tie(lo, ro) = split(o, x);
		o = merge(merge(lo, alloc()->assign(null, x)), ro);
		return o;
	}
	node *remove(node *&o, int x) {
		node *lo, *mo, *ro;
		tie(lo, mo) = split(o, x - 1);
		tie(mo, ro) = split(mo, x);
		o = merge(merge(lo, merge(mo->ls, mo->rs)), ro);
		return o;
	}
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
			int s = o->ch[d]->size;
			if (k == s + 1)
				return o;
			bool ok = !(k <= s);
			o = o->ch[ok];
			if (ok)
				k -= s + 1;
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
template<typename tp, size_t dsn, size_t pon>
typename treap<tp, dsn, pon>::node *treap<tp, dsn, pon>::node::null;

#endif
