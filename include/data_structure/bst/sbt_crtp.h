#pragma once

#include "data_structure/allocator.h"
#include "data_structure/base.h"
#include "data_structure/bst/bst_crtp.h"

namespace sbt {

namespace node {

template<class derived, typename key_t, bool has_fa>
using type = bst::node::type<derived, key_t, has_fa>;

}

namespace func {

using bst::util::link;
using bst::util::rotate;

template<class derived, class node>
class impl {
#define self static_cast<derived &>(*this)
	using key_t = typename node::key_type;
	void maintain(node *&t, int d) {
		if (!*t->ch[d])
			goto end;
		if (t->ch[d ^ 1]->size < t->ch[d]->ch[d]->size) {
			rotate(t, d);
		} else if (t->ch[d ^ 1]->size < t->ch[d]->ch[d ^ 1]->size) {
			rotate(t->ch[d], d ^ 1);
			rotate(t, d);
		} else {
			goto end;
		}
		maintain(t->ch[d], d);
		maintain(t->ch[d ^ 1], d ^ 1);
		maintain(t, 0);
		maintain(t, 1);
end:
		t->pull();
	}
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
			maintain(t, d);
		}
		return t;
	}
	// 返回删除的值, 模糊查找, 删除的值可以不在树里面.
	key_t remove(node *&t, key_t x) {
		if (!*t)
			return 0;
		int ret;
		/*
		 * case1: 找到合适的1个点.
		 * case2: 还在查找的途中.
		 */
		if (x == t->key || (x < t->key && !*t->ch[0]) || (t->key < x && !*t->ch[1])) {
			// case1.
			ret = t->key;// 此点必定被删除
			if(!*t->ch[0] || !*t->ch[1]) {// 对应后面2个条件, 删除的不一定是准确值.
				self.alloc(t);
				node *tmp = *t->ch[0] ? t->ch[0]: t->ch[1];
				if constexpr (node::has_fa())
					tmp->fa = t->fa;
				t = tmp;
			} else {
				// 替换成子树中最接近当前结点的值.
				bool d = t->ch[0]->size > t->ch[1]->size;
				t->key = remove(t->ch[d], t->key + (!d ? 1 : -1));
			}
		} else {
			// case2.
			ret = remove(t->ch[t->key < x], x);
		}
		if (*t)
			t->pull();
		return ret;
	}
#undef self
};

}

namespace root {

namespace detail {

template<class node>
class impl {
	template<class, class>
	friend class sbt::func::impl;
protected:
	allocator<node> alloc;
	void init() {
		alloc.clear();
		node *&null = node::null;
		null = new (alloc()) node(-1);
		null->size = 0;
		null->ch[0] = null->ch[1] = null;
	}
};

}

template<class node>
class single : public detail::impl<node> {
	using base = detail::impl<node>;
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

template<class node>
class multi : public detail::impl<node> {
	using base = detail::impl<node>;
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

