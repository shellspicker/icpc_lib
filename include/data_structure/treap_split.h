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
template<typename tp>
class __node {
public:
	using node = __node<tp>;
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
template<typename tp>
__node<tp> *__node<tp>::null;

template<typename tp, size_t pon = 0>
struct allocator {
	vector<tp *> buf;
	allocator() { buf.reserve(pon); }
	tp *operator ()(){
		buf.push_back(new tp());
		return buf.back();
	}
	void clear() {
		fup (i, 0, buf.size() - 1) if (buf[i])
			delete buf[i];
		buf.clear();
	}
};

template<typename tp, size_t dsn, size_t pon>
class treap {
public:
	using node = __node<tp>;
private:
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
		mo = merge(mo->ls, mo->rs);
		o = merge(merge(lo, mo), ro);
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
		node *last = o;
		o = o->fa;
		while (o != null && o->ch[d ^ 1] != last) {
			last = o;
			o = o->fa;
		}
		return o;
	}
	/*
	 * dir：0:左，1:右.
	 * k的有效范围应该是[1, o->size].
	 */
	node *kth(node *o, int k, bool d) {
		if (!inrange(k, 1, o->size))
			return null;
		while (o != null) {
			int s = o->ch[d]->size;
			if (k == s + 1)
				return o;
			if (k <= s)
				o = o->ch[d];
			else
				k -= s + 1, o = o->ch[d ^ 1];
		}
		return null;
	}
	/*
	 * 二分系列其实平衡树只能找到[)端点, 因为最后端点都会往右边超界.
	 * 如果返回排名的话, 对应ans得到的是[), ans-1得到的是(].
	 * 类似的还有直接返回对应结点, so, 能返回的信息有<rank, node*>.
	 * 把2个二分函数整合在一起, 后面2个bool参数对应括号的方向和形状.
	 */
	pair<int, node *> search(node *o, tp x, bool d, bool contain) {
		int ans = 1;// 从1开始标号.
		node *last = null;
		bool lastdir;
		while (o != null) {
			int s = o->ls->size;
			last = o;
			if (d == 0) {
				if (o->key < x)
					ans += s + 1, o = o->ch[d ^ 1], lastdir = d ^ 1;
				else
					o = o->ch[d], lastdir = d;
			}
			if (d == 1) {
				if (x < o->key)
					o = o->ch[d ^ 1], lastdir = d ^ 1;
				else
					ans += s + 1, o = o->ch[d], lastdir = d;
			}
		}
		ans = !d ? !contain ? ans - 1 : ans : contain ? ans - 1 : ans;
		node *endpos = !lastdir ? order(last, 0) : order(last, 1);
		// 如果最后的方向和期望方向一样, 那么答案是last点, 否则是endpos点.
		if (d != contain)// 找第一个.
			o = !lastdir ? last : endpos;
		else// 找最后一个.
			o = lastdir ? last : endpos;
		return make_pair(ans, o);
	}
};

#endif
