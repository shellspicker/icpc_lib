#pragma once

#include "data_structure/allocator.h"
#include "data_structure/base.h"
#include "data_structure/bst/bst_crtp.h"

namespace treap {

namespace node {

namespace detail {

struct priority {
	int fix = rand();
	priority() {}
	priority(int f) : fix(f) {}
};

template<class node, typename key_t, bool has_fa>
struct impl : bst::node::type<node, key_t, has_fa>, priority {
	using base = bst::node::type<node, key_t, has_fa>;
	impl() {}
	impl(key_t k) : base(k), priority() {}
	impl(key_t k, int f) : base(k), priority(f) {}
};

struct tag {};

template<class node, typename key_t, bool has_fa, class tag_t>
struct tag_impl : impl<node, key_t, has_fa>, tag {
	using tag_type = tag_t;
	using base = impl<node, key_t, has_fa>;
	using base::base;
	void release(const tag_t &arg) {
		if (!*this)
			return;
		this->self().release_impl(arg);
	}
	void push() {
		this->self().push_impl();
	}
	void release_impl(const tag_t &arg) {}
	void push_impl() {}
};

template<class base>
struct wrapper : base {
	using base::base;
	static constexpr bool has_tag() {
		return is_base_of_v<tag, base>;
	}
};

}

template<class node, typename key_t, bool has_fa>
using type = detail::wrapper<detail::impl<node, key_t, has_fa>>;
template<class node, typename key_t, bool has_fa, class tag_t>
using tag_type = detail::wrapper<detail::tag_impl<node, key_t, has_fa, tag_t>>;

}

namespace func {

using bst::util::link;
using bst::util::rotate;

namespace basic {

namespace split {

template<class derived, class node>
class impl {
#define self static_cast<derived &>(*this)
	using key_t = typename node::key_type;
	node *merge(node *lo, node *ro) {
		node *ret;
		if (!*lo || !*ro) {
			ret = !*lo ? ro : lo;
		} else {
			if (self.cmp(lo->fix, ro->fix)) {// heap.
				if constexpr (node::has_tag())
					lo->push();
				ro = merge(lo->ch[1], ro);
				ret = link(lo, 1, ro)->pull();
			} else {
				if constexpr (node::has_tag())
					ro->push();
				lo = merge(lo, ro->ch[0]);
				ret = link(ro, 0, lo)->pull();
			}
		}
		return ret;
	}
	pair<node *, node *> split_by_size(node *t, int k) {
		node *lo = node::null, *ro = node::null;
		if (*t) {
			if constexpr (node::has_tag())
				t->push();
			int s = t->ch[0]->size + 1;
			if (s <= k) {// note: <=.
				tie(lo, ro) = split_by_size(t->ch[1], k - s);
				lo = link(t, 1, lo)->pull();
			} else {
				tie(lo, ro) = split_by_size(t->ch[0], k);
				ro = link(t, 0, ro)->pull();
			}
		}
		return {lo, ro};
	}
	pair<node *, node *> split_by_key(node *t, key_t x) {
		node *lo = node::null, *ro = node::null;
		if (*t) {
			if (t->key <= x) {// note: <=.
				tie(lo, ro) = split_by_key(t->ch[1], x);
				lo = link(t, 1, lo)->pull();
			} else {
				tie(lo, ro) = split_by_key(t->ch[0], x);
				ro = link(t, 0, ro)->pull();
			}
		}
		return {lo, ro};
	}
protected:
	void segment_by_size(node *&t, int l, int r, node *&lo, node *&mo, node *&ro) {
		tie(mo, ro) = split_by_size(t, r);
		tie(lo, mo) = split_by_size(mo, l - 1);
	}
	void point_front_by_size(node *&t, int pos, node *&lo, node *&mo, node *&ro) {
		segment_by_size(t, pos, pos - 1, lo, mo, ro);
	}
	void point_back_by_size(node *&t, int pos, node *&lo, node *&mo, node *&ro) {
		segment_by_size(t, pos + 1, pos, lo, mo, ro);
	}
	void segment_by_key(node *&t, key_t l, key_t r, node *&lo, node *&mo, node *&ro) {
		tie(mo, ro) = split_by_key(t, r);
		tie(lo, mo) = split_by_key(mo, l - 1);
	}
	void point_front_by_key(node *&t, key_t k, node *&lo, node *&mo, node *&ro) {
		segment_by_key(t, k, k - 1, lo, mo, ro);
	}
	void point_back_by_key(node *&t, key_t k, node *&lo, node *&mo, node *&ro) {
		segment_by_key(t, k + 1, k, lo, mo, ro);
	}
	template<typename ...var>
	node *merge(node *t, var ...args) {
		initializer_list<int>{(t = merge(t, args), 0)...};
		return t;
	}
#undef self
};

}

template<class derived, class node>
class cartesian {
#define self static_cast<derived &>(*this)
	using key_t = typename node::key_type;
protected:
	void build(node *&t, const vector<key_t> &v) {
		node *last;
		stack<node *> st;
		auto get_chain = [&]() {
			node *now = t;
			last = t;
			while (*now) {
				if constexpr (node::has_fa())
					last = now;
				else
					st.push(now);
				now = now->ch[1];
			}
		};
		auto clear = [&]() {
			if constexpr (node::has_fa()) {
				while (*last)
					last = last->pull()->fa;
			} else {
				while (!st.empty()) {
					st.top()->pull();
					st.pop();
				}
			}
		};
		auto append = [&](node *&t, key_t x, int f) {
			node *o = new (self.alloc()) node(x, f), *lx = node::null;
			if constexpr (node::has_fa()) {
				while (*last && self.cmp(o->fix, last->fix))// heap.
					last = last->pull()->fa;
				lx = last->ch[1];
			} else {
				while (!st.empty() && self.cmp(o->fix, st.top()->fix)) {// heap.
					lx = st.top()->pull();
					st.pop();
				}
				last = st.empty() ? node::null : st.top();
			}
			link(o, 0, lx)->pull();
			link(last, 1, o);
			if constexpr (node::has_fa()) {
				last = o;
				if (!*o->fa)
					t = o;
			} else {
				st.push(o);
				if (st.size() == 1)
					t = o;
			}
		};
		get_chain();
		for (auto &x : v)
			append(t, x, rand());
		clear();
	}
#undef self
};

}

namespace bst {

template<class derived, class node>
class split_impl : public basic::split::impl<derived, node> {
#define self static_cast<derived &>(*this)
	using key_t = typename node::key_type;
	using base = basic::split::impl<derived, node>;
protected:
	void insert(node *&t, key_t x) {
		node *lo, *mo, *ro;
		base::point_front_by_key(t, x, lo, mo, ro);
		t = base::merge(lo, new (self.alloc()) node(x), ro);
	}
	void remove(node *&t, key_t x) {
		node *lo, *mo, *ro;
		base::segment_by_key(t, x, x, lo, mo, ro);
		self.alloc(mo);
		t = base::merge(lo, mo->ch[0], mo->ch[1], ro);
	}
#undef self
};

template<class derived, class node>
class rotate_impl {
#define self static_cast<derived &>(*this)
	using key_t = typename node::key_type;
protected:
	node *insert(node *&t, key_t x) {
		if (!*t) {
			t = new (self.alloc()) node(x);
		} else {
			bool d = t->key < x;// equal or not is don't care.
			if constexpr (node::has_fa())
				insert(t->ch[d], x)->fa = t;
			else
				insert(t->ch[d], x);
			if (self.cmp(t->ch[d]->fix, t->fix))// heap.
				rotate(t, d);
			t->pull();
		}
		return t;
	}
	// 有判断删除值存在.
	bool remove(node *&t, key_t x) {
		if (!*t)
			return 0;
		bool ok;
		if (x == t->key) {
			if (!*t->ch[0] || !*t->ch[1]) {
				self.alloc(t);
				node *tmp = *t->ch[0] ? t->ch[0] : t->ch[1];
				if constexpr (node::has_fa())
					tmp->fa = t->fa;
				t = tmp;
				ok = 1;
			} else {
				int d = (self.cmp(t->ch[0]->fix, t->ch[1]->fix) ? 0 : 1);// heap.
				rotate(t, d);
				ok = remove(t->ch[d ^ 1], x);
			}
		} else {
			ok = remove(t->ch[t->key < x], x);
		}
		if (*t)
			t->pull();
		return ok;
	}
#undef self
};

}

namespace segment {

template<class derived, class node>
class impl : public basic::split::impl<derived, node> {
	using key_t = typename node::key_type;
	using tag_t = typename node::tag_type;
	using base = basic::split::impl<derived, node>;
protected:
	void set_tag(node *&t, int l, int r, const tag_t &arg) {
		node *lo, *mo, *ro;
		base::segment_by_size(t, l, r, lo, mo, ro);
		mo->release(arg);
		t = base::merge(lo, mo, ro);
	}
	void visit(node *o, vector<key_t> &out) {
		if (!*o)
			return;
		o->push();
		visit(o->ch[0], out);
		out.emplace_back(o->key);
		visit(o->ch[1], out);
	}
};

}

}

namespace root {

namespace detail {

using namespace func;

template<class node, template<class> class fcmp>
class impl {
	template<class, class>
	friend class basic::split::impl;
	template<class, class>
	friend class basic::cartesian;
	template<class, class>
	friend class segment::impl;
	template<class, class>
	friend class bst::split_impl;
	template<class, class>
	friend class bst::rotate_impl;
protected:
	allocator<node> alloc;
	fcmp<int> cmp = fcmp<int>();
	void init() {
		alloc.clear();
		node *&null = node::null;
		null = new (alloc()) node();
		null->size = 0;
		null->ch[0] = null->ch[1] = null;
	}
};

}

template<class node, template<class> class fcmp>
class single : public detail::impl<node, fcmp> {
	using base = detail::impl<node, fcmp>;
protected:
	node *root;
public:
	void resize(size_t pon) {
		base::alloc.resize(pon);
	}
	void init() {
		base::init();
		root = node::null;
	}
};

template<class node, template<class> class fcmp>
class multi : public detail::impl<node, fcmp> {
	using base = detail::impl<node, fcmp>;
protected:
	vector<node *> root;
public:
	void resize(size_t pon, size_t dsn) {
		base::alloc.resize(pon);
		root.resize(dsn);
	}
	void init() {
		base::init();
		for (auto &o : root)
			o = node::null;
	}
	node *&operator [](int idx) {
		return root[idx];
	}
};

}

}

