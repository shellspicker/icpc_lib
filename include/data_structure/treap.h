#pragma once

#ifndef BST_MODE
#define BST_MODE SPLIT
#endif
#define SPLIT 0
#define ROTATE 1

/*
 * treap.
 * 宏: (FUNC_RANGE, FUNC_BST), BST_MODE(SPLIT, ROTATE), FATHER.
 * 随机优先级, 用系统的rand.
 * 堆性质, 大顶堆, 可修改.
 * 操作方式有旋转和非旋转(split, merge).
 * 插入一系列顺序排列的值, 可以使用insert_back, insert_back_over, 配套使用.
 *
 * FUNC_RANGE.
 * 区间树.
 * 只有非旋转.
 * 设置FATHER选择是否需要父结点.
 *
 * FUNC_BST.
 * 平衡树.
 * 设置BST_MODE选择旋转or非旋转.
 *
 * BST_MODE.
 * 选择旋转or非旋转模式, 默认非旋转模式.
 *
 * 旋转模式, 插入, 删除时, 维护堆性质.
 * 非旋转模式, merge时, 维护堆性质.
 */
template<typename tp, size_t dsn, size_t pon>
class treap : public bst<tp> {
#define ls ch[0]
#define rs ch[1]
#if FATHER
#  define link(u, d, v) ((u->ch[d] = v)->fa = u)
#else
#  define link(u, d, v) ((u->ch[d] = v), u)
#endif
	class node : public bst<tp>::node {
	public:
		static node *null;
		int fix;
		// 附加信息
		//int val;// map用.
#if FUNC_RANGE
		bool rev;
#endif
		node() {}
		node(tp k) : bst<tp>::node(k) {
			fix = rand();
#if FUNC_RANGE
			rev = 0;
#endif
		}
		node(tp k, int x) : bst<tp>::node(k), fix(x) {
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
	pair<node *, node *> split_by_size(node *t, int k) {
		node *lo = null, *ro = null;
		if (t != null) {
#if FUNC_RANGE
			t->push();
#endif
			int s = t->ls->size + 1;
			if (s <= k) {// note: <=.
				tie(lo, ro) = split_by_size((node *)t->ch[1], k - s);
				lo = (node *)link(t, 1, lo)->pull();
			} else {
				tie(lo, ro) = split_by_size((node *)t->ch[0], k);
				ro = (node *)link(t, 0, ro)->pull();
			}
		}
		return {lo, ro};
	}
	pair<node *, node *> split_by_val(node *t, tp x) {
		node *lo = null, *ro = null;
		if (t != null) {
			if (t->key <= x) {// note: <=.
				tie(lo, ro) = split_by_val((node *)t->ch[1], x);
				lo = (node *)link(t, 1, lo)->pull();
			} else {
				tie(lo, ro) = split_by_val((node *)t->ch[0], x);
				ro = (node *)link(t, 0, ro)->pull();
			}
		}
		return {lo, ro};
	}
	node *merge(node *lo, node *ro) {
		node *ret;
		if (lo == null || ro == null) {
			ret = lo == null ? ro : lo;
		} else {
			if (lo->fix > ro->fix) {// heap.
#if FUNC_RANGE
				lo->push();
#endif
				ro = merge((node *)lo->ch[1], ro);
				ret = (node *)link(lo, 1, ro)->pull();
			} else {
#if FUNC_RANGE
				ro->push();
#endif
				lo = merge(lo, (node *)ro->ch[0]);
				ret = (node *)link(ro, 0, lo)->pull();
			}
		}
		return ret;
	}
	template<typename ...var>
	node *merge(node *t, var ...args) {
		initializer_list<int>{(t = merge(t, args), 0)...};
		return t;
	}
	void segment_by_size(node *&t, int l, int r, node *&lo, node *&mo, node *&ro) {
		tie(mo, ro) = split_by_size(t, r);
		tie(lo, mo) = split_by_size(mo, l - 1);
	}
	void segment_by_val(node *&t, tp l, tp r, node *&lo, node *&mo, node *&ro) {
		tie(mo, ro) = split_by_val(t, r);
		tie(lo, mo) = split_by_val(mo, l - 1);
	}
#if FATHER
	void insert_back(node *&t, node *&last, tp x, int f) {
#else
	void insert_back(node *&t, vector<node *> &st, tp x, int f) {
#endif
		node *o = new (alloc()) node(x, f), *lx = null;
#if FATHER
		while (last != null && o->fix > last->fix)// heap.
			last = (node *)last->pull()->fa;
		lx = (node *)last->rs;
#else
		node *last;
		while (!st.empty() && o->fix > st.back()->fix) {// heap.
			lx = (node *)st.back()->pull();
			st.pop_back();
		}
		last = st.empty() ? null : st.back();
#endif
		link(o, 0, lx)->pull();
		link(last, 1, o);
#if FATHER
		last = o;
		if (o->fa == null)
			t = o;
#else
		st.push_back(o);
		if (st.size() == 1)
			t = o;
#endif
	}
#if FATHER
	void insert_back_over(node *&last) {
		while (last != null)
			last = (node *)last->pull()->fa;
	}
#else
	void insert_back_over(vector<node *> &st) {
		while (!st.empty()) {
			st.back()->pull();
			st.pop_back();
		}
	}
#endif
#if FATHER
	void build(node *&t, node *&last, vector<tp> &v) {
#else
	void build(node *&t, vector<node *> &st, vector<tp> &v) {
#endif
		for (auto x : v)
#if FATHER
			insert_back(t, last, x, rand());
		insert_back_over(last);
#else
			insert_back(t, st, x, rand());
		insert_back_over(st);
#endif
	}
#if FUNC_RANGE
	void reverse(node *&t, int l, int r) {
		node *lo, *mo, *ro;
		segment_by_size(t, l, r, lo, mo, ro);
		mo->release();
		t = merge(lo, mo, ro);
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
#if BST_MODE == SPLIT
	void insert(node *&t, tp x) {
		node *lo, *ro;
		tie(lo, ro) = split_by_val(t, x);
		t = merge(lo, new (alloc()) node(x), ro);
	}
	void remove(node *&t, tp x) {
		node *lo, *mo, *ro;
		segment_by_val(t, x, x, lo, mo, ro);
		alloc(mo);
		t = merge(lo, (node *)mo->ls, (node *)mo->rs, ro);
	}
#endif
#if BST_MODE == ROTATE
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
	node *insert(node *&t, tp x) {
		if (t == null) {
			t = new (alloc()) node(x);
		} else {
			bool d = t->key < x;// equal or not is don't care.
#if FATHER
			insert((node *&)t->ch[d], x)->fa = t;
#else
			insert((node *&)t->ch[d], x);
#endif
			if (((node *)t->ch[d])->fix > t->fix)// heap.
				rotate(t, d);
			t->pull();
		}
		return t;
	}
	// 有判断删除值存在.
	bool remove(node *&t, tp x) {
		if (t == null)
			return 0;
		bool ok;
		if (x == t->key) {
			if (t->ls == null || t->rs == null) {
				alloc(t);
				node *tmp = t->ls != null ? (node *)t->ls : (node *)t->rs;
#if FATHER
				tmp->fa = t->fa;
#endif
				t = tmp;
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
#endif
#endif
public:
	node *&null = node::null;// null must be reference.
	node *root[dsn];
#if FATHER
	node *last[dsn];
#else
	vector<node *> st[dsn];
#endif
	void init() {
		srand(time(0));// 这个加上有可能直接RE, 慎重.
		alloc.clear();
		null = new (alloc()) node(-1);
		bst<tp>::null = null;
		null->size = 0;
		null->ls = null->rs = null;
		fup (i, 0, dsn - 1) {
			root[i] = null;
#if FATHER
			last[i] = null;
#else
			st[i].clear();
#endif
		}
	}
	node *&operator ()(int idx) {
		return root[idx];
	}
#if FUNC_RANGE
	void build(int tid, vector<tp> &v) {
#if FATHER
		build(root[tid], last[tid], v);
#else
		build(root[tid], st[tid], v);
#endif
	}
	void reverse(int tid, int l, int r) {
		reverse(root[tid], l, r);
	}
	void print(int tid, vector<tp> &out) {
		out.clear();
		visit(root[tid], out);
	}
#endif
#if FUNC_BST
	void insert(int tid, tp x) {
		insert(root[tid], x);
	}
	void remove(int tid, tp x) {
		remove(root[tid], x);
	}
#endif
#undef ls
#undef rs
#undef link
};
template<typename tp, size_t dsn, size_t pon>
typename treap<tp, dsn, pon>::node *treap<tp, dsn, pon>::node::null;

#undef BST_MODE
#undef SPLIT
#undef ROTATE
#undef FATHER
#undef FUNC_RANGE
#undef FUNC_BST

