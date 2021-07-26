/*
 * include:
 *   data_structure/allocator.h
 */
template<class derived, typename tp>
struct left_heap_node {
	using vtp = tp;
	static derived *null;
	tp key;
	int dist;
	derived *ls, *rs;
	left_heap_node() {
		ls = rs = null;
		dist = 0;
	}
	left_heap_node(tp x) : left_heap_node() {
		key = x;
	}
	operator bool() { return this != null; }
	void pull() {
		dist = rs->dist + 1;
	}
};
template<class derived, typename tp>
derived *left_heap_node<derived, tp>::null;

template<class node, template<typename> class fcmp>
class left_heap {
	using vtp = typename node::vtp;
	allocator<node> alloc;
	vector<node *> root;
	node *&null = node::null;
	fcmp<vtp> cmp = fcmp<vtp>();
public:
	using node_t = node;
	left_heap() {}
	node *&operator [](int i) { return root[i]; }
	int operator ()(node *o) { return o - null - 1; }
	void resize(size_t ds_n, size_t mem_n) {
		root.resize(ds_n);
		alloc.resize(mem_n);
	}
	void init() {
		alloc.clear();
		null = alloc();
		null->dist = -1;
		fup_range (i, 0, root.size())
			root[i] = null;
	}
private:
	node *merge(node *mas, node *slv) {
		if (!*mas || !*slv)
			return *mas ? mas : slv;
		if (!cmp(mas->key, slv->key))
			swap(mas, slv);
		mas->rs = merge(mas->rs, slv);
		if (!(mas->rs->dist < mas->ls->dist))
			swap(mas->ls, mas->rs);
		mas->pull();
		return mas;
	}
	void push(node *&rt, vtp x) {
		node *o = new (alloc()) node(x);
		rt = merge(rt, o);
	}
	void pop(node *&rt) {
		if (!*rt)
			return;
		alloc(rt);
		rt = merge(rt->ls, rt->rs);
	}
public:
	void push(int i, vtp x) { push(root[i], x); }
	void pop(int i) { pop(root[i]); }
	node *top(int i) { return root[i]; }
	node *merge(int a, int b) { return merge(root[a], root[b]); }
};
