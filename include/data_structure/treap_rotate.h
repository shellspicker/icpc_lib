#ifndef TREAP_ROTATE_H
#define TREAP_ROTATE_H 1

/*
 * treap, rotate版本.
 * 优先级用系统的rand.
 * 这里是大顶堆, rotate之前都会判断堆的性质, 需要改的话找调用rotate的地方.
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
	node *rotate(node *&o, int d) {
		auto link = [](node *u, int d, node *v) {
			return (u->ch[d] = v)->fa = u;
		};
		node *k = o->ch[d], *ac = o->fa;
		link(o, d, k->ch[d ^ 1])->pull();
		link(k, d ^ 1, o);
		(o = k)->fa = ac;
		return o;
	}
	// multiset
	void insert(node *&o, node *f, tp x) {
		if (o == null)
			o = alloc()->assign(!f ? null : f, x);
		else {
			bool d = o->key < x;// equal or not is don't care.
			insert(o->ch[d], o, x);
			if (o->ch[d]->fix > o->fix)// heap.
				rotate(o, d);
			o->pull();
		}
	}
	// map, set
	/*
	bool insert(node *&o, node *f, tp x, int count=1)
	{
		bool ok = 1;
		if (o == null) {
			// 第一次插入x, map[x] = 1.
			o = alloc()->assign(!f ? null : f, x);
			o->val = count;
			return ok;
		} else {
			//if(x==o->key) return 0;// 普通的set, 重复值直接返回.
			if(x==o->key) {// map, cnt+=count.
				o->val += count;
				return 1;
			}
			bool d = o->key < x;// equal or not is don't care.
			ok = insert(o->ch[d], o, x, count);
			if(o->ch[d]->fix > o->fix)// heap.
				rotate(o, d);
			o->pull();
		}
		return ok;
	}
	*/
	//有判断删除值存在
	bool remove(node *&o, tp x) {
		if (o == null)
			return 0;
		bool ok;
		if (x == o->key) {
			if (o->ls == null || o->rs == null) {
				node *fa = o->fa;
				(o = o->ls != null ? o->ls : o->rs)->fa = fa;
				ok = 1;
			} else {
				int d = (o->ls->fix > o->rs->fix ? 0 : 1);
				ok = remove(rotate(o, d)->ch[d ^ 1], x);
			}
		} else {
			ok = remove(o->ch[o->key < x], x);
		}
		if (o != null)
			o->pull();
		return ok;
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
