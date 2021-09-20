#pragma once

#include "data_structure/allocator.h"
#include "data_structure/base.h"
#include "data_structure/bst/bst_crtp.h"

namespace splay {

namespace node {

namespace detail {

template<class node, typename key_t, bool has_fa>
using impl = bst::node::type<node, key_t, has_fa>;

struct tag {};

template<class node, typename key_t, bool has_fa, class tag_t>
struct tag_impl : bst::node::type<node, key_t, has_fa> , tag {
	using tag_type = tag_t;
	using base = bst::node::type<node, key_t, has_fa>;
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
	using key_t = typename base::key_type;
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

namespace segment {

template<class, class>
class impl;

}

namespace bst {

template<class, class>
class impl;

}

using ::bst::util::link;
using ::bst::util::rotate;

namespace basic {

template<class node>
class topdown {
	using key_t = typename node::key_type;
	template<class, class>
	friend class segment::impl;
	template<class, class>
	friend class bst::impl;
public:
	void select_by_key(node *&t, key_t x) {
#define magic_go(master, d, other)\
		go = master->ch[d];\
		other = link(master, d, other);\
		master = go
		node *o = t, *lr[2] = {node::null, node::null}, *go, *fa;
		if constexpr (node::has_fa())
			fa = t->fa;
		if (!*o)
			return;
		while (o->key != x) {
			bool d = o->key < x;
			if (!*o->ch[d])
				break;
			if (*o->ch[d]->ch[d]) {
				key_t dk = o->ch[d]->key;
				if ((!d && x < dk) || (d && dk < x)) {
					rotate(o, d);
					if (o->key == x)
						break;
				}
			}
			magic_go(o, d, lr[d]);
			if constexpr (node::has_fa())
				link(node::null, d, o);
		}
		fup_range (d, 0, 2) {
			while (*lr[d]) {
				magic_go(lr[d], d, o->ch[d ^ 1]);
				o->ch[d ^ 1]->pull();
			}
			if constexpr (node::has_fa())
				link(o, d ^ 1, o->ch[d ^ 1]);
		}
		(t = o)->pull();
		if constexpr (node::has_fa())
			t->fa = fa;
#undef magic_go
	}
	void select_by_size(node *&t, int k) {
#define finded()\
		if constexpr (node::has_tag())\
			o->push();\
		s = o->ch[0]->size + 1;\
		if (k == s)\
			break
#define magic_go(master, d, other)\
		go = master->ch[d];\
		other = link(master, d, other);\
		master = go
		node *o = t, *lr[2] = {node::null, node::null}, *go, *fa;
		if constexpr (node::has_fa())
			fa = t->fa;
		int s;
		if (!*o)
			return;
		while (*o) {
			finded();
			bool d = s < k;
			if constexpr (node::has_tag())
				o->ch[d]->push();
			int ss = o->ch[d]->ch[0]->size + 1;
			if (((!d && k < ss) || (d && ss < k - s))) {
				rotate(o, d);
				finded();
			}
			magic_go(o, d, lr[d]);
			if constexpr (node::has_fa())
				link(node::null, d, o);
			if (d)
				k -= s;
		}
		fup_range (d, 0, 2) {
			while (*lr[d]) {
				magic_go(lr[d], d, o->ch[d ^ 1]);
				o->ch[d ^ 1]->pull();
			}
		if constexpr (node::has_fa())
			link(o, d ^ 1, o->ch[d ^ 1]);
		}
		(t = o)->pull();
		if constexpr (node::has_fa())
			t->fa = fa;
#undef finded
#undef magic_go
	}
};

template<class node>
class downtop {
	using key_t = typename node::key_type;
	template<class, class>
	friend class segment::impl;
	template<class, class>
	friend class bst::impl;
public:
	void select_node(node *&t, node *x) {
#define get(u, v, d) u = v->fa, d = u->ch[1] == v
		node *y, *z, *ac = t->fa;
		bool dy, dz;
		while (x->fa != ac) {
			get(y, x, dy);
			get(z, y, dz);
			if (z != ac && dz == dy)
				rotate(z, dz);
			rotate(y, dy);
		}
		x->pull();
		if (x->fa == ac)
			t = x;
#undef get
	}
	void select_by_key(node *&t, key_t x) {
		node *o = t, *last = o;
		if (!*t)
			return;
		while (*o) {
			if constexpr (node::has_tag())
				o->push();
			if (o->key == x)
				break;
			last = o;
			o = o->ch[o->key < x];
		}
		if (!*o)
			o = last;
		select_node(t, o);
	}
	void select_by_size(node *&t, int k) {
		node *o = t, *fa = t->fa;
		if (!*t)
			return;
		while (*o) {
			if constexpr (node::has_tag())
				o->push();
			int s = o->ch[0]->size + 1;
			if (s == k)
				break;
			bool d = s < k;
			o = o->ch[d];
			if (d)
				k -= s;
		}
		select_node(t, o);
	}
};

}

namespace segment {

template<
	class derived,
	class node>
class impl {
#define self static_cast<derived &>(*this)
	using key_t = typename node::key_type;
	using tag_t = typename node::tag_type;
public:
	void build(node *f, bool d, node *&t, const vector<key_t> &v) {
		function<node *(node *, bool, node *&, int, int)> helper =
		[&](node *f, bool d, node *&t, int l, int r) {
			if (!length(l, r))
				return node::null;
			int mid = midpoint(l, r);
			t = new (self.alloc()) node(v[mid]);
			if constexpr (node::has_fa())
				link(f, d, t);
			helper(t, 0, t->ch[0], l, mid - 1);
			helper(t, 1, t->ch[1], mid + 1, r);
			t->pull();
			return t;
		};
		helper(f, d, t, 0, v.size() - 1);
	}
	node *&segment(node *&t, int l, int r) {
		l++, r++;
		self.select_by_size(t, r + 1);
		self.select_by_size(t->ch[0], l - 1);
		return (node *&)t->ch[0]->ch[1];
	}
	node *&all(node *&t) {
		return segment(t, 1, t->size - 2);
	}
	void pull(node *&t) {
		t->ch[0]->pull();
		t->pull();
	}
	void build_all(node *&t, const vector<key_t> &v) {
		node *&sub = all(t);
		build(t->ch[0], 1, sub, v);
		pull(t);
	}
	void set_tag(node *&t, int l, int r, const tag_t &arg) {
		node *&sub = segment(t, l, r);
		sub->release(arg);
		pull(t);
	}
	void visit(node *t, vector<key_t> &out) {
		function<void(node *)> helper = [&](node *o) {
			if (!*o)
				return;
			o->push();
			helper(o->ch[0]);
			out.emplace_back(o->key);
			helper(o->ch[1]);
		};
		node *&sub = all(t);
		helper(sub);
		pull(t);
	}
#undef self
};

}

namespace bst {

template<
	class derived,
	class node
>
class impl {
#define self static_cast<derived &>(*this)
	using key_t = typename node::key_type;
public:
	void insert(node *&t, key_t x) {
		node *o = new (self.alloc()) node(x);
		if (!*t) {
			t = o;
		} else {
			self.select_by_key(t, x);
			bool d = t->key < x;// equal or not is don't care.
			link(o, d, t->ch[d]);
			t->ch[d] = node::null;
			t = link(o, d ^ 1, t->pull());
		}
		t->pull();
		if constexpr (node::has_fa())
			t->fa = node::null;
	}
	void remove(node *&t, key_t x) {
		self.select_by_key(t, x);
		if (t->key != x)
			return;
		self.alloc(t);
		if (!*t->ch[0] || !*t->ch[1]) {
			t = !*t->ch[0] ? t->ch[1] : t->ch[0];
		} else {
			bool d = t->ch[0]->size > t->ch[1]->size;
			self.select_by_key(t->ch[d], t->key + (d ? -1 : 1));
			t = link(t->ch[d], d ^ 1, t->ch[d ^ 1]);
		}
		if (*t)
			t->pull();
		if constexpr (node::has_fa())
			t->fa = node::null;
	}
#undef self
};

}

}

namespace root {

namespace detail {

using namespace splay::func;

template<class node>
class impl {
	template<class, class>
	friend class segment::impl;
	template<class, class>
	friend class bst::impl;
protected:
	allocator<node> alloc;
	void init() {
		alloc.clear();
		node *&null = node::null;
		null = new (alloc()) node();
		null->size = 0;
		null->ch[0] = null->ch[1] = null;
	}
};

}

using ::bst::util::link;

template<class node>
class single : public detail::impl<node> {
	using base = detail::impl<node>;
protected:
	node *root;
	pair<node *, node *> nos;
public:
	void resize(size_t pon) {
		base::alloc.resize(pon);
	}
	void init() {
		base::init();
		if constexpr (node::has_tag()) {
			nos.first = new (base::alloc()) node();
			nos.second = new (base::alloc()) node();
			root = link(nos.first, 1, nos.second)->pull();
		} else {
			root = node::null;
		}
	}
};

template<class node>
class multi : public detail::impl<node> {
	using base = detail::impl<node>;
protected:
	vector<node *> root;
	vector<pair<node *, node *>> nos;
public:
	void resize(size_t pon, size_t dsn) {
		base::alloc.resize(pon);
		root.resize(dsn);
		nos.resize(dsn);
	}
	void init() {
		base::init();
		if constexpr (node::has_tag()) {
			fup_range (i, 0, root.size()) {
				nos[i].first = new (base::alloc()) node();
				nos[i].second = new (base::alloc()) node();
				root[i] = link(nos[i].first, 1, nos[i].second)->pull();
			}
		} else {
			for (auto &o : root)
				o = node::null;
		}
	}
};

}

}

